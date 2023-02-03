package application.repository;

import application.models.Client;
import application.models.ClientHobbies;
import application.repository.generic.DataBaseRepository;
import application.utils.DataBase;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Optional;

public class ClientRepository extends DataBaseRepository<Long, Client> {
    public ClientRepository(DataBase dataBase) {
        super(dataBase);
    }

    @Override
    public Optional<Client> extractEntity(ResultSet resultSet) throws SQLException {
        long id = resultSet.getLong("client_id");
        String name = resultSet.getString("name");
        int fidelityGrade = resultSet.getInt("fidelity_grade");
        int age = resultSet.getInt("age");
        ClientHobbies hobby = ClientHobbies.valueOf(resultSet.getString("hobbies"));
        return Optional.of(new Client(id, name, fidelityGrade, age, hobby));
    }

    @Override
    public List<Client> findAll() {
        return null;
    }

    public Optional<Client> find(Long aLong) {
        List<Client> results = findQueryResults("SELECT * FROM clients WHERE client_id = " + aLong);
        if (results.isEmpty()) {
            return Optional.empty();
        }
        return Optional.of(results.get(0));
    }
}
