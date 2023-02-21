package application.models;

public class Contact extends Friend {
    private final Message lastMessage;

    public Contact(Friend friend, Message lastMessage) {
        super(friend, friend.getFriendsFrom(), friend.getCommonFriends());
        this.lastMessage = lastMessage;
    }

    public Message getLastMessage() {
        return lastMessage;
    }
}
