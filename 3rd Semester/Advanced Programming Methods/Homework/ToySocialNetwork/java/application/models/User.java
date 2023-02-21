package application.models;

import application.models.exceptions.ValidationException;
import application.utils.Encoder;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.Objects;
import java.util.UUID;

/**
 * The class <b>User</b> represents the client using the social media app.
 */
public class User extends Entity<UUID> {
    private final MailAddress mailAddress;
    private final String firstName;
    private final String lastName;
    private final String password;
    private final LocalDate registerDate;
    private final LocalDate birthDate;
    private final String biography;
    private final Avatar avatar;

    /**
     * Constructs a new User, the data must be validated, if you need to create a new User, use User.create() instead.
     *
     * @param id           UUID, the identifier of the User
     * @param mailAddress  String, the email address of the User, already validated
     * @param firstName    String, the first name of the User, validated
     * @param lastName     String, the last name of the User, validated
     * @param password     String, the password of the User, validated
     * @param registerDate LocalDate, the register-date of the User, validated
     * @param birthDate    LocalDate, the birthdate of the User, validated
     * @param biography    String, the biography of the User, validated
     * @param avatar       Avatar, the avatar of the User
     */
    public User(UUID id, MailAddress mailAddress, String firstName, String lastName, String password,
                LocalDate registerDate, LocalDate birthDate, String biography, Avatar avatar) {
        super(id);
        this.mailAddress = mailAddress;
        this.firstName = firstName;
        this.lastName = lastName;
        this.password = password;
        this.registerDate = registerDate;
        this.birthDate = birthDate;
        this.biography = biography;
        this.avatar = avatar;
    }

    public static User create(String mailAddress, String firstName, String lastName, String password,
                              LocalDate birthDate, String biography, Avatar avatar) throws ValidationException {
        String error = "";
        MailAddress mail = null;
        try {
            mail = MailAddress.of(mailAddress);
        }
        catch (ValidationException e) {
            error += e.getMessage() + "\n";
        }

        if (firstName == null || firstName.equals("") || firstName.equalsIgnoreCase("null")) {
            error += "The first name must not be null\n";
        }
        else if (firstName.length() < 2) {
            error += "The first name must have at least 2 characters\n";
        }
        else if (firstName.length() > 32) {
            error += "The first name must have at most 32 characters\n";
        }
        else if (!firstName.matches("^[A-Z][a-zA-Z-0-9]*$")) {
            error += "The first name doesn't respect the format\n";
        }

        if (lastName == null || lastName.equals("") || lastName.equalsIgnoreCase("null")) {
            error += "The last name must not be null\n";
        }
        else if (lastName.length() < 2) {
            error += "The last name must have at least 2 characters\n";
        }
        else if (lastName.length() > 64) {
            error += "The last name must have at most 64 characters\n";
        }
        else if (!lastName.matches("^([A-Z][a-zA-Z-0-9]* *)+$")) {
            error += "The last name doesn't respect the format\n";
        }

        if (password == null) {
            error += "The password mustn't be null\n";
        }
        else if (password.length() < 5 || password.length() > 24) {
            error += "The password must have between 5 and 24 characters\n";
        }

        if (birthDate == null) {
            error += "The birth date must not be null\n";
        }
        else if (birthDate.isAfter(LocalDate.now()) || birthDate.plusYears(120).isBefore(LocalDate.now())) {
            error += "Invalid birth date\n";
        }

        if (biography != null && biography.length() > 100) {
            error += "The biography must have at most 100 characters\n";
        }

        if (!error.isEmpty()) {
            throw new ValidationException(error.substring(0, error.length() - 1));
        }

        return new User(UUID.randomUUID(), mail, firstName, lastName, Encoder.encode(password), LocalDate.now(), birthDate, biography, avatar);
    }

    /**
     * @return the email address of the User
     */
    public MailAddress getMailAddress() {
        return mailAddress;
    }

    /**
     * @return the first name of the User
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * @return the last name of the User
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * @return the full name of the User
     */
    public String getName() {
        return firstName + ' ' + lastName;
    }

    /**
     * @return the encoded password of the User
     */
    public String getPassword() {
        return password;
    }

    /**
     * @return the register date of the User
     */
    public LocalDate getRegisterDate() {
        return registerDate;
    }

    /**
     * @return the birthdate of the User
     */
    public LocalDate getBirthDate() {
        return birthDate;
    }
    public short getAge() {
        return (short) ChronoUnit.YEARS.between(birthDate, LocalDate.now());
    }

    /**
     * @return the biography of the User
     */
    public String getBiography() {
        return biography;
    }

    public Avatar getAvatar() {
        return avatar;
    }

    @Override
    public String toString() {
        return firstName + ' ' + lastName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        User user = (User) o;
        return Objects.equals(getID(), user.getID());
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode());
    }
}
