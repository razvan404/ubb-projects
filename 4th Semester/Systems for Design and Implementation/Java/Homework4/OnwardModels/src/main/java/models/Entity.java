package models;

import java.io.Serializable;

public class Entity<ID> implements Serializable {
    private ID id;

    public Entity(ID id) {
        this.id = id;
    }
    public Entity() {}

    public ID getID() {
        return id;
    }

    public void setID(ID identifier) {
        id = identifier;
    }
}
