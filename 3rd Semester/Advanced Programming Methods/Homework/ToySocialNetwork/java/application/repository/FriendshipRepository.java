package application.repository;

import application.models.Friendship;
import application.utils.pair.DistinctPair;

import java.util.UUID;

public interface FriendshipRepository extends AbstractRepository<DistinctPair<UUID>, Friendship> {
    void deleteFriendshipsOf(UUID user);
}