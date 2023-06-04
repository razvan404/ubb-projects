package api.models;

import java.io.Serializable;

public class Identifiable<ID> implements Serializable {
    private ID id;

    public Identifiable(ID id) {
        this.id = id;
    }
    public Identifiable() {}

    public ID getID() {
        return id;
    }

    public void setID(ID identifier) {
        id = identifier;
    }
}
