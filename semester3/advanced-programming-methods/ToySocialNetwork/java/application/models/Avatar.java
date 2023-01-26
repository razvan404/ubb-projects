package application.models;

import javafx.scene.image.Image;

public class Avatar extends Entity<Short> {
    private final Image photo;

    public Avatar(Short aShort, Image photo) {
        super(aShort);
        this.photo = photo;
    }

    public Image getPhoto() {
        return photo;
    }

    @Override
    public String toString() {
        return "Avatar " + getID() + ": " + photo.getUrl();
    }
}
