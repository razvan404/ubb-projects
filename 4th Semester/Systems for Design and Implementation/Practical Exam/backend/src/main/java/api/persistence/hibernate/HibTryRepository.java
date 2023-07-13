package api.persistence.hibernate;

import api.models.Try;
import api.persistence.TryRepository;
import org.springframework.stereotype.Component;

import java.util.UUID;

@Component
public class HibTryRepository extends HibCrudRepository<UUID, Try> implements TryRepository {
}
