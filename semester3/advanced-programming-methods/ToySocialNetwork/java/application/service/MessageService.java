package application.service;

import application.models.Contact;
import application.models.Friend;
import application.models.Message;
import application.models.exceptions.ValidationException;
import application.repository.MessageRepository;
import application.service.exceptions.AlreadyExistsException;

import java.util.List;
import java.util.UUID;

public class MessageService {
    private final MessageRepository repository;


    public MessageService(MessageRepository repository) {
        this.repository = repository;
    }

    public void save(UUID fromUser, UUID toUser, String message) throws ValidationException, AlreadyExistsException {
        if (repository.save(Message.create(fromUser, toUser, message)).isPresent()) {
            throw new AlreadyExistsException("There is already an message with the same identifier! (please contact an administrator)");
        }
    }

    public List<Message> getMessagesBetween(UUID firstUser, UUID secondUser) {
        return repository.getMessagesBetween(firstUser, secondUser);
    }

    public List<Contact> getContactList(UUID user, List<Friend> friends) {
        return repository.getContactList(user, friends).stream().sorted((o1, o2) -> {
            if (o1.getLastMessage() != null && o2.getLastMessage() != null) {
                return -o1.getLastMessage().getTime().compareTo(o2.getLastMessage().getTime());
            }
            if (o1.getLastMessage() != null) {
                return -1;
            }
            if (o2.getLastMessage() != null) {
                return 1;
            }
            return o1.getName().compareTo(o2.getName());
        }).toList();
    }
}
