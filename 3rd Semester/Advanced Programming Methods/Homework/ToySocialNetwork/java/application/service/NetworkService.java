package application.service;

import application.models.*;
import application.models.exceptions.ValidationException;
import application.models.notification.Notification;
import application.models.notification.NotificationType;
import application.service.exceptions.AlreadyExistsException;
import application.service.exceptions.NotFoundException;
import application.utils.Constants;

import java.time.LocalDate;
import java.util.*;

/**
 * The class <b>NetworkService</b> is used to manipulate data from more services related to the social network.
 */
public class NetworkService {
    public final UserService userService;
    public final FriendshipService friendshipService;
    public final CommunityService communityService;
    public final NotificationService notificationService;
    public final MessageService messageService;
    private Friend currentUser;

    public NetworkService(UserService userService, FriendshipService friendshipService,
                          CommunityService communityService, NotificationService notificationService,
                          MessageService messageService) {
        this.userService = userService;
        this.friendshipService = friendshipService;
        this.communityService = communityService;
        this.notificationService = notificationService;
        this.messageService = messageService;
    }


    public void login(String mailAddress, String password) throws NotFoundException {
        User user = userService.getUserByMailAndPassword(mailAddress, password);
        currentUser = new Friend(user, null, 0);
    }

    public void register(String mailAddress, String firstName, String lastName, String password, LocalDate birthDate) throws ValidationException, AlreadyExistsException {
        User user = userService.save(mailAddress, firstName, lastName, password, birthDate);
        notificationService.save(Constants.SERVER_UUID, user.getID(), "Welcome to Chatter!",
                "Hey " + user.getName() + ", this is a notification, bet you never saw something like" +
                        " this!", NotificationType.INFORMATIVE);
        currentUser = new Friend(user, null, 0);
    }

    public Friend getCurrentUser() {
        return currentUser;
    }

    public List<Friend> findByName(String subString) {
        return userService.findByName(currentUser.getID(), subString);
    }

    public List<Friend> findCommonFriends(UUID user) {
        return userService.findCommonFriends(currentUser.getID(), user);
    }

    public List<Friend> findFriendsOf(UUID user) {
        return userService.findFriendsOf(currentUser.getID(), user);
    }

    public Friend findFriend(UUID userID) throws NotFoundException {
        if (currentUser.getID().equals(userID)) {
            return new Friend(currentUser, null, 0);
        }
        return userService.findFriend(currentUser.getID(), userID);
    }

    public List<Notification> getNotificationList() {
        return notificationService.findUserNotifications(currentUser.getID());
    }

    public Notification getFriendRequest(UUID user) {
        return notificationService.getFriendRequest(currentUser.getID(), user);
    }

    public void sendFriendRequest(UUID friendID) throws ValidationException, AlreadyExistsException {
        notificationService.save(currentUser.getID(), friendID, "New friend request",
                "You have an incoming friend request from " + currentUser.getName() + "!",
                NotificationType.FRIEND_REQUEST);
    }

    public void acceptFriendRequest(Notification friendRequest) throws ValidationException, AlreadyExistsException {
        friendshipService.save(friendRequest.getFromUser(), friendRequest.getToUser());
        notificationService.save(currentUser.getID(), friendRequest.getFromUser(), "Friend acceptance",
                currentUser.getName() + " accepted you into their " + "friend list!",
                NotificationType.FRIEND_REQUEST_ACCEPTED);
        notificationService.delete(friendRequest.getID());
    }

    public void rejectFriendRequest(Notification notification) throws ValidationException, AlreadyExistsException {
        notificationService.save(currentUser.getID(), notification.getFromUser(), "Friend rejection",
                currentUser.getName() + " did not accept you into their friend list!",
                NotificationType.FRIEND_REQUEST_REJECTED);
        notificationService.delete(notification.getID());
    }

    public void removeFriend(UUID friendID) throws ValidationException, AlreadyExistsException, NotFoundException {
        friendshipService.delete(currentUser.getID(), friendID);
        notificationService.save(currentUser.getID(), friendID, "Friend removal",
                currentUser.getName() + " removed you from their friend list!",
                NotificationType.FRIEND_REMOVED);
    }

    public void updateCurrentUser(String mailAddress, String firstName, String lastName, String password,
                                  LocalDate birthDate, String biography, Avatar avatar)
            throws ValidationException, AlreadyExistsException, NotFoundException {
        userService.update(currentUser, mailAddress, firstName, lastName, password, birthDate, biography, avatar);
        currentUser = new Friend(userService.find(currentUser.getID()), null, 0);
    }

    public void deleteCurrentUser(String mailAddress, String password) throws NotFoundException {
        if (!userService.getUserByMailAndPassword(mailAddress, password).equals(currentUser)) {
            throw new NotFoundException("Invalid mail address / password");
        }
        notificationService.deleteNotificationsOf(currentUser.getID());
        friendshipService.deleteFriendshipsOf(currentUser.getID());
        userService.delete(currentUser);
    }

    public List<Contact> getContactList() {
        return messageService.getContactList(currentUser.getID(), findFriendsOf(currentUser.getID()));
    }

    public List<Message> getMessagesWith(UUID user) {
        return messageService.getMessagesBetween(currentUser.getID(), user);
    }

    public void sendMessageTo(UUID user, String message) throws ValidationException, AlreadyExistsException {
        messageService.save(currentUser.getID(), user, message);
    }
}