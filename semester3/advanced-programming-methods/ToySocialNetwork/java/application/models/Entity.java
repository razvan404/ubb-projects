package application.models;

import java.io.Serial;
import java.io.Serializable;
import java.util.Objects;

/**
 * The class <b>Entity</b> should be used by all the objects in this application that have an identifier.
 * @param <ID> the type of the identifier
 */
public class Entity<ID> implements Serializable {
    @Serial
    private static final long serialVersionUID = 1101111000L;

    private final ID id;

    /**
     * Constructs an Entity with a given identifier.
     * @param id the identifier of the Entity
     */
    public Entity(ID id) {
        this.id = id;
    }

    /**
     * @return the identifier of the Entity
     */
    public ID getID() {
        return id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Entity<?> entity = (Entity<?>) o;
        return Objects.equals(id, entity.id);
    }
}
