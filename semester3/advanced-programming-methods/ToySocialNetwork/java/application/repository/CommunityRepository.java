package application.repository;

import application.models.Community;

import java.util.Optional;
import java.util.UUID;

public interface CommunityRepository {
    Optional<Community> extractCommunityFrom(UUID user);
}
