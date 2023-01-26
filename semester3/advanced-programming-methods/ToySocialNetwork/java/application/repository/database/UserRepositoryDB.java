package application.repository.database;

import application.models.Avatar;
import application.models.Friend;
import application.models.MailAddress;
import application.models.User;
import application.models.exceptions.ValidationException;
import application.repository.UserRepository;
import application.repository.file.AvatarRepositoryFile;
import application.utils.database.DataBase;

import java.sql.Date;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.sql.*;

public class UserRepositoryDB extends AbstractRepositoryDB<UUID, User> implements UserRepository {
    public UserRepositoryDB(DataBase dataBase) {
        super(dataBase, "users");
    }

    @Override
    public Optional<User> extractEntity(ResultSet resultSet) throws SQLException {
        UUID id = resultSet.getObject("user_id", UUID.class);
        String email = resultSet.getString("email");
        String firstName = resultSet.getString("first_name");
        String lastName = resultSet.getString("last_name");
        String password = resultSet.getString("password");
        LocalDate registerDate = resultSet.getDate("register_date").toLocalDate();
        LocalDate birthDate = resultSet.getDate("birth_date").toLocalDate();
        String biography = resultSet.getString("biography");
        Avatar avatar = AvatarRepositoryFile.getInstance().find(resultSet.getShort("avatar_id"))
                .orElse(null);

        try {
            return Optional.of(new User(id, MailAddress.of(email), firstName, lastName, password,
                    registerDate, birthDate, biography, avatar));
        } catch (ValidationException validationException) {
            throw new RuntimeException(validationException);
        }
    }

    public Optional<Friend> extractFriend(ResultSet resultSet) throws SQLException {
        User user = extractEntity(resultSet).orElseThrow(() -> new RuntimeException("Database error"));
        LocalDateTime friendsFrom = null;
        if (resultSet.getTimestamp("friends_from") != null) {
            friendsFrom = resultSet.getTimestamp("friends_from").toLocalDateTime();
        }
        int commonFriends = resultSet.getInt("common_friends");
        return Optional.of(new Friend(user, friendsFrom, commonFriends));
    }

    @Override
    protected PreparedStatement findStatement(Connection connection, UUID id) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "SELECT * " +
            "FROM users " +
            "WHERE user_id = ?");

        preparedStatement.setObject(1, id, Types.OTHER);
        return preparedStatement;
    }

    @Override
    protected PreparedStatement saveStatement(Connection connection, User user) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "INSERT INTO users(user_id, email, first_name, last_name, password, register_date, birth_date, biography) " +
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        preparedStatement.setObject(1, user.getID(), Types.OTHER);
        preparedStatement.setString(2, user.getMailAddress().toString());
        preparedStatement.setString(3, user.getFirstName());
        preparedStatement.setString(4, user.getLastName());
        preparedStatement.setString(5, user.getPassword());
        preparedStatement.setDate(6, Date.valueOf(user.getRegisterDate()));
        preparedStatement.setDate(7, Date.valueOf(user.getBirthDate()));
        preparedStatement.setString(8, user.getBiography());
        return preparedStatement;
    }

    @Override
    protected PreparedStatement deleteStatement(Connection connection, UUID id) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "DELETE FROM users " +
            "WHERE user_id = ?");
        preparedStatement.setObject(1, id, Types.OTHER);
        return preparedStatement;
    }

    @Override
    protected PreparedStatement updateStatement(Connection connection, User user) throws SQLException {
        PreparedStatement preparedStatement = connection.prepareStatement(
        "UPDATE users " +
            "SET email = ?, first_name = ?, last_name = ?, password = ?, birth_date = ?, biography = ?, avatar_id = ? " +
            "WHERE user_id = ?");
        preparedStatement.setString(1, user.getMailAddress().toString());
        preparedStatement.setString(2, user.getFirstName());
        preparedStatement.setString(3, user.getLastName());
        preparedStatement.setString(4, user.getPassword());
        preparedStatement.setDate(5, Date.valueOf(user.getBirthDate()));
        preparedStatement.setString(6, user.getBiography());
        preparedStatement.setShort(7, user.getAvatar().getID());
        preparedStatement.setObject(8, user.getID(), Types.OTHER);
        System.out.println(preparedStatement);
        return preparedStatement;
    }

    @Override
    public Optional<User> findByMail(String mail) {
        if (mail == null) {
            throw new IllegalArgumentException("The mail address must not be null!");
        }
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
                    "SELECT * " +
                            "FROM users " +
                            "WHERE email = ?");
            preparedStatement.setString(1, mail);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return extractEntity(resultSet);
            }

        } catch (SQLException ignored) {}
        return Optional.empty();
    }

    @Override
    public List<Friend> findFriendsOf(UUID fromUserID, UUID ofUserID) {
        List<Friend> friends = new ArrayList<>();
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement;
            if (!fromUserID.equals(ofUserID)) {
                preparedStatement = connection.prepareStatement(
                "SELECT U.*, F.friends_from AS friends_from " +
                     "FROM ( " +
                     "    SELECT U.*, COUNT(F2) AS common_friends " +
                     "    FROM ( " +
                     "        SELECT U.* " +
                     "        FROM users U INNER JOIN friendships F on U.user_id = F.first_user " +
                     "        WHERE F.second_user = ? " +
                     "        UNION " +
                     "        SELECT U.* " +
                     "        FROM users U INNER JOIN friendships F on U.user_id = F.second_user " +
                     "        WHERE F.first_user = ?) U " +
                     "    INNER JOIN friendships F1 ON F1.first_user = U.user_id OR F1.second_user = U.user_id " +
                     "    LEFT JOIN friendships F2 ON (F2.first_user = ? AND F2.second_user = F1.first_user AND F1.first_user != U.user_id) " +
                     "                            OR (F2.second_user = ? AND F2.first_user = F1.first_user AND F1.first_user != U.user_id) " +
                     "                            OR (F2.first_user = ? AND F2.second_user = F1.second_user AND F1.second_user != U.user_id) " +
                     "                            OR (F2.second_user = ? AND F2.first_user = F1.second_user AND F1.second_user != U.user_id) " +
                     "    GROUP BY user_id, email, first_name, last_name, password, register_date, birth_date, biography, avatar_id) U " +
                     "LEFT JOIN friendships F ON (first_user = U.user_id AND second_user = ?) " +
                     "                        OR (second_user = U.user_id AND first_user = ?) " +
                     "ORDER BY U.first_name, U.last_name;"
                );
                preparedStatement.setObject(1, ofUserID, Types.OTHER);
                preparedStatement.setObject(2, ofUserID, Types.OTHER);
                preparedStatement.setObject(3, fromUserID, Types.OTHER);
                preparedStatement.setObject(4, fromUserID, Types.OTHER);
                preparedStatement.setObject(5, fromUserID, Types.OTHER);
                preparedStatement.setObject(6, fromUserID, Types.OTHER);
                preparedStatement.setObject(7, fromUserID, Types.OTHER);
                preparedStatement.setObject(8, fromUserID, Types.OTHER);
            }
            else {
                preparedStatement = connection.prepareStatement(
                "SELECT F.*, COUNT(F2) AS common_friends " +
                    "FROM (SELECT U.*, F.friends_from AS friends_from " +
                    "    FROM users U INNER JOIN friendships F on U.user_id = F.first_user " +
                    "    WHERE F.second_user = ? " +
                    "    UNION " +
                    "    SELECT U.*, F.friends_from AS friends_from " +
                    "    FROM users U INNER JOIN friendships F on U.user_id = F.second_user " +
                    "    WHERE F.first_user = ?) F " +
                    "LEFT JOIN friendships F1 ON F1.first_user = F.user_id OR F1.second_user = F.user_id " +
                    "LEFT JOIN friendships F2 ON (F2.first_user = ? AND F2.second_user = F1.first_user AND F1.first_user != F.user_id) " +
                    "                        OR (F2.second_user = ? AND F2.first_user = F1.first_user AND F1.first_user != F.user_id) " +
                    "                        OR (F2.first_user = ? AND F2.second_user = F1.second_user AND F1.second_user != F.user_id) " +
                    "                        OR (F2.second_user = ? AND F2.first_user = F1.second_user AND F1.second_user != F.user_id) " +
                    "GROUP BY F.user_id, F.email, F.first_name, F.last_name, F.password, F.register_date, F.birth_date, F.biography, F.avatar_id, F.friends_from;");
                preparedStatement.setObject(1, ofUserID);
                preparedStatement.setObject(2, ofUserID);
                preparedStatement.setObject(3, fromUserID);
                preparedStatement.setObject(4, fromUserID);
                preparedStatement.setObject(5, fromUserID);
                preparedStatement.setObject(6, fromUserID);
            }

            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                extractFriend(resultSet).ifPresent(friends::add);
            }
        }
        catch (SQLException ignored) {}
        return friends;
    }

    @Override
    public List<Friend> findByName(UUID fromUserID, String match) {
        List<Friend> friends = new ArrayList<>();
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "SELECT U.*, F1.friends_from AS friends_from, count(F3) AS common_friends " +
                "FROM users U " +
                "   LEFT JOIN friendships F1 ON F1.first_user = user_id AND F1.second_user = ?" +
                "   LEFT JOIN friendships F2 ON F1.first_user = F2.first_user OR F1.first_user = F2.second_user " +
                "   LEFT JOIN friendships F3 ON (F1.first_user = F2.first_user AND F3.second_user = F2.second_user AND F3.first_user = ?) " +
                "       OR (F1.first_user = F2.second_user AND F3.second_user = F2.first_user AND F3.first_user = ?) " +
                "       OR (F1.first_user = F2.first_user AND F3.first_user = F2.second_user AND F3.second_user = ?) " +
                "       OR (F1.first_user = F2.second_user AND F3.first_user = F2.first_user AND F3.second_user = ?) " +
                "WHERE (CONCAT(first_name, ' ', last_name) ILIKE ? OR CONCAT(last_name, ' ', first_name) ILIKE ?) " +
                "   AND user_id <= ? " +
                "GROUP BY user_id, email, first_name, last_name, password, register_date, birth_date, biography, avatar_id, F1.friends_from " +
                "UNION " +
                "SELECT U.*, F1.friends_from AS friends_from, count(F3) AS common_friends " +
                "FROM users U " +
                "   LEFT JOIN friendships F1 ON F1.second_user = user_id AND F1.first_user = ? " +
                "   LEFT JOIN friendships F2 ON F1.second_user = F2.first_user OR F1.second_user = F2.second_user " +
                "   LEFT JOIN friendships F3 ON (F1.first_user = F2.first_user AND F3.second_user = F2.second_user AND F3.first_user = ?) " +
                "       OR (F1.first_user = F2.second_user AND F3.second_user = F2.first_user AND F3.first_user = ?) " +
                "       OR (F1.first_user = F2.first_user AND F3.first_user = F2.second_user AND F3.second_user = ?) " +
                "       OR (F1.first_user = F2.second_user AND F3.first_user = F2.first_user AND F3.second_user = ?) " +
                "WHERE (CONCAT(first_name, ' ', last_name) ILIKE ? OR CONCAT(last_name, ' ', first_name) ILIKE ?) " +
                "   AND user_id >= ? " +
                "GROUP BY user_id, email, first_name, last_name, password, register_date, birth_date, biography, avatar_id, F1.friends_from " +
                "ORDER BY common_friends DESC, first_name, last_name " +
                "LIMIT 10");
            preparedStatement.setObject(1, fromUserID, Types.OTHER);
            preparedStatement.setObject(2, fromUserID, Types.OTHER);
            preparedStatement.setObject(3, fromUserID, Types.OTHER);
            preparedStatement.setObject(4, fromUserID, Types.OTHER);
            preparedStatement.setObject(5, fromUserID, Types.OTHER);
            preparedStatement.setString(6, "%" + match + "%");
            preparedStatement.setString(7, "%" + match + "%");
            preparedStatement.setObject(8, fromUserID, Types.OTHER);

            preparedStatement.setObject(9, fromUserID, Types.OTHER);
            preparedStatement.setObject(10, fromUserID, Types.OTHER);
            preparedStatement.setObject(11, fromUserID, Types.OTHER);
            preparedStatement.setObject(12, fromUserID, Types.OTHER);
            preparedStatement.setObject(13, fromUserID, Types.OTHER);
            preparedStatement.setString(14, "%" + match + "%");
            preparedStatement.setString(15, "%" + match + "%");
            preparedStatement.setObject(16, fromUserID, Types.OTHER);

            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                extractFriend(resultSet).ifPresent(friends::add);
            }
        } catch (SQLException ignored) {}
        return friends;
    }

    @Override
    public List<Friend> findCommonFriends(UUID fromUserID, UUID withUserID) {
        List<Friend> friends = new ArrayList<>();
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "SELECT U.*, COUNT(F2) AS common_friends " +
                "FROM (SELECT U.*, F2.friends_from " +
                "      FROM users U " +
                "        INNER JOIN friendships F1 ON (F1.first_user = U.user_id AND F1.second_user = ?) " +
                "                                OR (F1.second_user = U.user_id AND F1.first_user = ?) " +
                "        INNER JOIN friendships F2 ON (F2.first_user = U.user_id AND F2.second_user = ?) " +
                "                                OR (F2.second_user = U.user_id AND F2.first_user = ?)) U " +
                "    INNER JOIN friendships F1 ON (F1.first_user = U.user_id OR F1.second_user = U.user_id) " +
                "                            AND F1.first_user != ? AND F1.second_user != ? " +
                "    LEFT JOIN friendships F2 ON ((F2.second_user = F1.first_user OR F2.second_user = F1.second_user) AND F2.first_user = ?) " +
                "                            OR ((F2.first_user = F1.first_user OR F2.first_user = F1.second_user) AND F2.second_user = ?) " +
                "GROUP BY U.user_id, U.email, U.first_name, U.last_name, U.password, U.register_date, U.birth_date, U.biography, U.avatar_id, U.friends_from");

            preparedStatement.setObject(1, fromUserID, Types.OTHER);
            preparedStatement.setObject(2, fromUserID, Types.OTHER);
            preparedStatement.setObject(3, withUserID, Types.OTHER);
            preparedStatement.setObject(4, withUserID, Types.OTHER);
            preparedStatement.setObject(5, fromUserID, Types.OTHER);
            preparedStatement.setObject(6, fromUserID, Types.OTHER);
            preparedStatement.setObject(7, fromUserID, Types.OTHER);
            preparedStatement.setObject(8, fromUserID, Types.OTHER);

            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                extractFriend(resultSet).ifPresent(friends::add);
            }
        } catch (SQLException ignored) {}
        return friends;
    }

    @Override
    public Optional<Friend> findFriend(UUID fromUserID, UUID friendID) {
        try (Connection connection = getConnection()) {
            PreparedStatement preparedStatement = connection.prepareStatement(
            "SELECT U.*, F1.friends_from AS friends_from, count(F3) AS common_friends " +
                "FROM users U " +
                "    LEFT JOIN friendships F1 ON F1.first_user = user_id " +
                "    LEFT JOIN friendships F2 ON F1.first_user = F2.first_user OR F1.first_user = F2.second_user " +
                "    LEFT JOIN friendships F3 ON (F1.first_user = F2.first_user AND F3.second_user = F2.second_user AND F3.first_user = ?) " +
                "      OR (F1.first_user = F2.second_user AND F3.second_user = F2.first_user AND F3.first_user = ?) " +
                "      OR (F1.first_user = F2.first_user AND F3.first_user = F2.second_user AND F3.second_user = ?) " +
                "      OR (F1.first_user = F2.second_user AND F3.first_user = F2.first_user AND F3.second_user = ?) " +
                "WHERE user_id = ? AND user_id <= ? " +
                "GROUP BY user_id, email, first_name, last_name, password, register_date, birth_date, biography, avatar_id, F1.friends_from UNION " +
                "SELECT U.*, F1.friends_from AS friends_from, count(F3.first_user) AS common_friends " +
                "FROM users U " +
                "    LEFT JOIN friendships F1 ON F1.second_user = user_id" +
                "    LEFT JOIN friendships F2 ON F1.second_user = F2.first_user OR F1.second_user = F2.second_user " +
                "    LEFT JOIN friendships F3 ON (F1.first_user = F2.first_user AND F3.second_user = F2.second_user AND F3.first_user = ?) " +
                "      OR (F1.first_user = F2.second_user AND F3.second_user = F2.first_user AND F3.first_user = ?) " +
                "      OR (F1.first_user = F2.first_user AND F3.first_user = F2.second_user AND F3.second_user = ?) " +
                "      OR (F1.first_user = F2.second_user AND F3.first_user = F2.first_user AND F3.second_user = ?) " +
                "WHERE user_id = ? AND user_id >= ? " +
                "GROUP BY user_id, email, first_name, last_name, password, register_date, birth_date, biography, avatar_id, F1.friends_from");

            preparedStatement.setObject(1, fromUserID, Types.OTHER);
            preparedStatement.setObject(2, fromUserID, Types.OTHER);
            preparedStatement.setObject(3, fromUserID, Types.OTHER);
            preparedStatement.setObject(4, fromUserID, Types.OTHER);
            preparedStatement.setObject(5, friendID, Types.OTHER);
            preparedStatement.setObject(6, fromUserID, Types.OTHER);


            preparedStatement.setObject(7, fromUserID, Types.OTHER);
            preparedStatement.setObject(8, fromUserID, Types.OTHER);
            preparedStatement.setObject(9, fromUserID, Types.OTHER);
            preparedStatement.setObject(10, fromUserID, Types.OTHER);
            preparedStatement.setObject(11, friendID, Types.OTHER);
            preparedStatement.setObject(12, fromUserID, Types.OTHER);

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return extractFriend(resultSet);
            }
        } catch (SQLException ignored) {}

        return Optional.empty();
    }
}