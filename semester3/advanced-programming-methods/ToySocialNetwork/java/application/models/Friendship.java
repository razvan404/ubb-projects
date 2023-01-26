package application.models;

import application.models.exceptions.ValidationException;
import application.utils.pair.DistinctPair;

import java.time.LocalDateTime;
import java.util.UUID;

/** The class <b>Friendship</b> represents the relation between two Users.
 *
 */
public class Friendship extends Entity<DistinctPair<UUID>> {
    private final LocalDateTime friendsFrom;
    /**
     * Constructs a Friendship, the data should be already validated, if you need to create a new Friendship use Friendship.create() instead.
     *
     * @param user1         UUID, the identifier of the first User in the Friendship
     * @param user2         UUID, the identifier of the second User in the Friendship
     * @param friendsFrom   LocalDateTime, the time when the Users became friends
     */
    public Friendship(UUID user1, UUID user2, LocalDateTime friendsFrom) {
        super(new DistinctPair<>(user1, user2));
        this.friendsFrom = friendsFrom;
    }

    public static Friendship create(UUID user1, UUID user2) throws ValidationException {
        if (user1 == null) {
            throw new IllegalArgumentException("First user's identifier must not be null.");
        }
        if (user2 == null) {
            throw new IllegalArgumentException("Second user's identifier must not be null.");
        }
        if (user1.equals(user2)) {
            throw new ValidationException("You need 2 different users to create a friendship.");
        }
        return new Friendship(user1, user2, LocalDateTime.now());
    }

    /**
     * @return the date when the Users became friends
     */
    public LocalDateTime getFriendshipDate() {
        return friendsFrom;
    }

    /**
     * Verifies if an User is in a Friendship.
     * @param user the User to verify if it's in the Friendship
     * @return the UUID of his friend if the User is in the Friendship,
     *         null otherwise
     */
    public UUID contains(User user) {
        if (getID().first().equals(user.getID())) {
            return getID().second();
        }
        if (getID().second().equals(user.getID())) {
            return getID().first();
        }
        return null;
    }
}
