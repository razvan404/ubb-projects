package application.models;

public abstract class Entity<ID> {
    private ID id;
    public Entity(ID id) {
        this.id = id;
    }
    public ID getID() {
        return id;
    }
}
