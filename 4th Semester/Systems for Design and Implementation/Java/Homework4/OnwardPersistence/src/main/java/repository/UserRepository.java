package repository;

import models.User;

import java.util.UUID;

public interface UserRepository extends CrudRepository<UUID, User> {
    User tryLogin(String username, String password);
}
