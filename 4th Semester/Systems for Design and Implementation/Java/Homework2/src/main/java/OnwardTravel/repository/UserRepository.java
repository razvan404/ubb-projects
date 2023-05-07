package OnwardTravel.repository;

import OnwardTravel.models.User;
import OnwardTravel.repository.exceptions.DataLoadException;

import java.util.UUID;

public interface UserRepository extends CrudRepository<UUID, User> {
    User tryLogin(String username, String password) throws DataLoadException;
}
