package application.models;

import application.models.exceptions.ValidationException;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.UUID;

public class Friend extends User {
    private final LocalDateTime friendsFrom;
    private final int commonFriends;

    /**
     * Constructs a new User, the data should be validated, if you need to create a new User, use User.create() instead.
     *
     * @param id           UUID, the identifier of the User
     * @param mailAddress  String, the email address of the User, already validated
     * @param firstName    String, the first name of the User, validated
     * @param lastName     String, the last name of the User, validated
     * @param password     String, the password of the User, validated
     * @param registerDate LocalDate, the register-date of the User, validated
     * @param birthDate    LocalDate, the birthdate of the User, validated
     * @param biography    String, the biography of the User, validated
     */
    public Friend(UUID id, MailAddress mailAddress, String firstName, String lastName, String password, LocalDate registerDate,
                  LocalDate birthDate, String biography, Avatar avatar, LocalDateTime friendsFrom, int commonFriends) throws ValidationException {
        super(id, mailAddress, firstName, lastName, password, registerDate, birthDate, biography, avatar);
        this.friendsFrom = friendsFrom;
        this.commonFriends = commonFriends;
    }

    public Friend(User user, LocalDateTime friendsFrom, int commonFriends) {
        super(user.getID(), user.getMailAddress(), user.getFirstName(), user.getLastName(), user.getPassword(),
                user.getRegisterDate(), user.getBirthDate(), user.getBiography(), user.getAvatar());
        this.friendsFrom = friendsFrom;
        this.commonFriends = commonFriends;
    }

    public LocalDateTime getFriendsFrom() {
        return friendsFrom;
    }

    public int getCommonFriends() {
        return commonFriends;
    }
}
