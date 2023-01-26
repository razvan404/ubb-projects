package application.repository;

import application.models.Friend;
import application.models.User;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

public interface UserRepository extends AbstractRepository<UUID, User> {
    List<Friend> findFriendsOf(UUID fromUserID, UUID ofUserID);

    Optional<User> findByMail(String mail);

    /**
     * Finds the first 10 Friends that match a string, sorted by the number of common friends of the User who made the request
     * @param fromUserID the identifier of the User who made the request
     * @param match the String to match
     * @return List of Friend, the first 10 matches
     */
    List<Friend> findByName(UUID fromUserID, String match);

    List<Friend> findCommonFriends(UUID fromUserID, UUID toUserID);
    Optional<Friend> findFriend(UUID fromUserID, UUID friendID);
}
