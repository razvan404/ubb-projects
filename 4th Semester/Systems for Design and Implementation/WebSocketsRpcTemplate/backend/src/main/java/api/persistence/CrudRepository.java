package api.persistence;

import api.models.Identifiable;

import java.io.Serializable;
import java.util.List;

public interface CrudRepository<ID extends Serializable, E extends Identifiable<ID>> {
    E findOne(ID id);
    List<E> findAll();
    E save(E entity);
    E update(E entity);
    E delete(ID id);
}
