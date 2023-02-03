package application.repository.generic;

import application.models.Entity;

import java.util.List;
import java.util.Optional;

public interface Repository<ID, E extends Entity<ID>> {
    List<E> findAll();
}
