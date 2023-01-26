package application.repository.database;

import application.models.*;
import application.models.exceptions.ValidationException;
import application.repository.CommunityRepository;
import application.repository.file.AvatarRepositoryFile;
import application.utils.database.DataBase;

import java.sql.*;
import java.time.LocalDate;
import java.util.*;

public class CommunityRepositoryDB implements CommunityRepository {
    private final DataBase dataBase;
    public CommunityRepositoryDB(DataBase dataBase) {
        this.dataBase = dataBase;
    }

    protected Connection getConnection() throws SQLException {
        return dataBase.getConnection();
    }

    private Optional<User> extractUser(ResultSet resultSet) throws SQLException {
        UUID id = resultSet.getObject("user_id", UUID.class);
        String email = resultSet.getString("email");
        String password = resultSet.getString("password");
        String firstName = resultSet.getString("first_name");
        String lastName = resultSet.getString("last_name");
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
    @Override
    public Optional<Community> extractCommunityFrom(UUID userID) {
        List<User> users = new ArrayList<>();
        Map<UUID, List<UUID>> uuidMap = new HashMap<>();

        try (Connection connection = getConnection()) {
            PreparedStatement extractUserStatement = connection.prepareStatement(
            "SELECT * " +
                "FROM users " +
                "WHERE user_id = ?"
            );
            PreparedStatement extractFriendsStatement = connection.prepareStatement(
            "SELECT second_user AS friend_id " +
                "FROM friendships " +
                "WHERE first_user = ? " +
                "UNION " +
                "SELECT first_user AS friend_id " +
                "FROM friendships " +
                "WHERE second_user = ?"
            );
            Stack<UUID> userStack = new Stack<>();
            Set<UUID> visited = new HashSet<>();

            userStack.push(userID);
            visited.add(userID);

            while (!userStack.isEmpty()) {
                UUID current = userStack.pop();

                extractUserStatement.setObject(1, current, Types.OTHER);
                extractFriendsStatement.setObject(1, current, Types.OTHER);
                extractFriendsStatement.setObject(2, current, Types.OTHER);

                ResultSet extractUserResultSet = extractUserStatement.executeQuery();
                User user;
                extractUserResultSet.next();
                user = extractUser(extractUserResultSet).orElseThrow();
                users.add(user);

                List<UUID> friendList = new ArrayList<>();
                ResultSet resultSet = extractFriendsStatement.executeQuery();
                while (resultSet.next()) {
                    UUID friend = resultSet.getObject("friend_id", UUID.class);
                    friendList.add(friend);
                    if (!visited.contains(friend)) {
                        userStack.push(friend);
                        visited.add(friend);
                    }
                }
                uuidMap.put(current, friendList);
            }
        } catch (SQLException ignored) {}

        if (users.size() < Community.MINIMUM_MEMBERS) {
            return Optional.empty();
        }
        return Optional.of(new Community(users, uuidMap));
    }
}
