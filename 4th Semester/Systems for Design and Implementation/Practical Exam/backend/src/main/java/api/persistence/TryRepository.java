package api.persistence;

import api.models.Try;

import java.util.UUID;

public interface TryRepository extends CrudRepository<UUID, Try> {
}
