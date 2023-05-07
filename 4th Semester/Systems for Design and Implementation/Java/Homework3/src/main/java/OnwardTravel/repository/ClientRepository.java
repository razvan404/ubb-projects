package OnwardTravel.repository;

import OnwardTravel.models.Client;

import java.util.UUID;

public interface ClientRepository extends CrudRepository<UUID, Client> {
    Client findByNameAndPhone(String name, String phoneNumber);
}
