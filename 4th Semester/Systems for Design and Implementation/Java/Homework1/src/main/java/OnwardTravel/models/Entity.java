package OnwardTravel.models;

public class Entity<ID> {
    private ID id;

    public Entity(ID id) {
        this.id = id;
    }
    public Entity() {}

    public ID getID() {
        return id;
    }

    public void setID(ID identifier) {
        this.id = id;
    }
}
