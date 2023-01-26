package application.service;

import application.models.Friendship;
import application.utils.pair.DistinctPair;
import application.models.exceptions.ValidationException;
import application.repository.FriendshipRepository;
import application.service.exceptions.AlreadyExistsException;
import application.service.exceptions.NotFoundException;

import java.util.UUID;

/**
 * The class <b>FriendshipService</b> is used to manipulate data from FriendshipRepository.
 */
public class FriendshipService {
    private final FriendshipRepository repository;
    /**
     * Constructs a new FriendshipService.
     * @param repository the repository associated with the repository
     */
    public FriendshipService(FriendshipRepository repository) {
        this.repository = repository;
    }

    /**
     * Saves a Friendship into the repository.
     * @param user1 a reference for the first User
     * @param user2 a reference for the second User
     * @throws ValidationException when the two users cannot create a Friendship
     */
    public void save(UUID user1, UUID user2) throws AlreadyExistsException, ValidationException {
        if (repository.save(Friendship.create(user1, user2)).isPresent()) {
            throw new AlreadyExistsException("There is already a friendship between these 2 users!");
        }
    }

    /**
     * Deletes a Friendship from the repository.
     * @param user1 a reference for the first User
     * @param user2 a reference for the second User
     */
    public void delete(UUID user1, UUID user2) throws NotFoundException {
        if (repository.delete(new DistinctPair<>(user1, user2)).isEmpty()) {
            throw new NotFoundException("There is no friendship between the specified users!");
        }
    }

    public void deleteFriendshipsOf(UUID user) {
        repository.deleteFriendshipsOf(user);
    }

    public int size() {
        return repository.size();
    }
}
