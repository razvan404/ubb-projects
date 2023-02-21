package application.repository;

import application.models.Contact;
import application.models.Friend;
import application.models.Message;

import java.util.List;
import java.util.UUID;

public interface MessageRepository extends AbstractRepository<Long, Message> {
    List<Message> getMessagesBetween(UUID firstUser, UUID secondUser);
    List<Contact> getContactList(UUID user, List<Friend> friendList);
}
