package application.service;

import application.models.Avatar;
import application.models.Friend;
import application.models.MailAddress;
import application.models.User;
import application.models.exceptions.ValidationException;
import application.repository.UserRepository;
import application.service.exceptions.AlreadyExistsException;
import application.service.exceptions.NotFoundException;
import application.utils.Encoder;

import java.time.LocalDate;
import java.util.List;
import java.util.UUID;

/**
 * The class <b>UserService</b> is used to manipulate data from UserRepository.
 */
public class UserService {
    private final UserRepository repository;
    /**
     * Constructs a new UserService
     * @param repository the repository associated with the service
     */
    public UserService(UserRepository repository) {
        this.repository = repository;
    }

    /**
     * Finds all the Users that contains a substring in their names.
     * @param fromUser the user who is doing the request
     * @param subString the substring that the Users should contain
     * @return first 10 Users that contains the substring given as a parameter
     */
    public List<Friend> findByName(UUID fromUser, String subString) {
        return repository.findByName(fromUser, subString);
    }

    public List<Friend> findCommonFriends(UUID fromUser, UUID withUser) {
        return repository.findCommonFriends(fromUser, withUser);
    }

    public List<Friend> findFriendsOf(UUID fromUser, UUID withUser) {
        return repository.findFriendsOf(fromUser, withUser);
    }
    public Friend findFriend(UUID fromUser, UUID friendID) throws NotFoundException {
        return repository.findFriend(fromUser, friendID).orElseThrow(() -> new NotFoundException("There is no user with given identifier!"));
    }

    /**
     * Creates and saves a new User with the given data.
     * @param email the email address of the new User
     * @param firstName the first name of the new User
     * @param lastName the last name of the New User
     * @throws AlreadyExistsException when there is already another User with the same email / identifier
     * @throws ValidationException when the data about the User is invalid
     */
    public User save(String email, String firstName, String lastName, String password, LocalDate birthDate) throws AlreadyExistsException, ValidationException {
        if (repository.findByMail(email).isPresent())  {
            throw new AlreadyExistsException("The save could not be done because there is already a user with the same email address.");
        }
        User toSave = User.create(email, firstName, lastName, password, birthDate, null, null);
        if (repository.save(toSave).isPresent()) {
            throw new AlreadyExistsException("The save could not be done because there is already one user with the same identifier!");
        }
        return toSave;
    }

    /**
     * Deletes the User given as parameter.
     * @param user the User to be deleted
     * @throws NotFoundException when there is no such User in the Repository
     */
    public void delete(User user) throws NotFoundException {
        repository.delete(user.getID())
                .orElseThrow(() -> new NotFoundException("There deletion could not be done because there is no such user!"));
    }

    /**
     * Updates a User with the given data.
     * @param user the User to be updated
     * @param newMailAddress String, the new mail address of the User
     * @param newFirstName String, the new first name of the User
     * @param newLastName String, the new last name of the User
     * @param newPassword String, the new password of the User
     * @param newBirthDate LocalDate, the new birthdate of the User
     * @param newBiography String, the new biography of the User
     */
    public void update(User user, String newMailAddress, String newFirstName, String newLastName, String newPassword,
                       LocalDate newBirthDate, String newBiography, Avatar newAvatar) throws ValidationException, AlreadyExistsException, NotFoundException {
        if (newMailAddress != null && !user.getMailAddress().toString().equals(newMailAddress) && repository.findByMail(newMailAddress).isPresent()) {
            throw new AlreadyExistsException("The update could not be done because there is already another user with the same email address.");
        }
        if (newMailAddress == null || newMailAddress.equals("")) {
            newMailAddress = user.getMailAddress().toString();
        }
        if (newFirstName == null || newFirstName.equals("")) {
            newFirstName = user.getFirstName();
        }
        if (newLastName == null || newLastName.equals("")) {
            newLastName = user.getLastName();
        }
        if (newPassword == null || newPassword.equals("")) {
            newPassword = user.getPassword();
        }
        else {
            if (newPassword.length() < 5) {
                throw new ValidationException("The password should have at least 5 characters.");
            }
            newPassword = Encoder.encode(newPassword);
        }
        if (newBirthDate == null) {
            newBirthDate = user.getBirthDate();
        }
        if (newBiography == null || newBiography.equals("")) {
            newBiography = user.getBiography();
        }

        if (newAvatar == null) {
            newAvatar = user.getAvatar();
        }

        User.create(newMailAddress, newFirstName, newLastName, newPassword, newBirthDate, newBiography, newAvatar);

        repository.update(new User(user.getID(), MailAddress.of(newMailAddress), newFirstName, newLastName, newPassword, user.getRegisterDate(), newBirthDate, newBiography, newAvatar))
                .orElseThrow(() -> new NotFoundException("The update could not be done because the specified user doesn't exist!"));
    }

    public User find(UUID id) throws NotFoundException {
        return repository.find(id).orElseThrow(() -> new NotFoundException("There is no user with the given identifier!"));
    }

    public User getUserByMailAndPassword(String mailAddress, String password) throws NotFoundException {
        User user = repository.findByMail(mailAddress).orElseThrow(() -> new NotFoundException("Invalid mail address / password"));
        if (user.getPassword().equals(Encoder.encode(password))) {
            return user;
        }
        throw new NotFoundException("Invalid mail address / password");
    }

    public int size() {
        return repository.size();
    }
}
