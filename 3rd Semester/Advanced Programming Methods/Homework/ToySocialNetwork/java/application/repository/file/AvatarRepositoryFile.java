package application.repository.file;

import application.configuration.Config;
import application.models.Avatar;
import application.repository.AvatarRepository;
import javafx.scene.image.Image;

import java.util.Collection;
import java.util.List;

public class AvatarRepositoryFile extends AbstractRepositoryFile<Short, Avatar> implements AvatarRepository {
    private static final AvatarRepositoryFile instance = new AvatarRepositoryFile();

    /**
     * Constructs a new AvatarRepositoryFile.
     */
    private AvatarRepositoryFile() {
        super(Config.getProperty("avatars_file"));
    }

    public static AvatarRepositoryFile getInstance() {
        return instance;
    }

    @Override
    public Collection<Avatar> findAll() {
        return entities.values();
    }

    @Override
    protected Avatar extractEntity(List<String> attributes) {
        return new Avatar(Short.valueOf(attributes.get(0)), new Image("/application/gui/media/avatars/" + attributes.get(1)));
    }

    @Override
    protected String entityAsString(Avatar entity) {
        return entity.getID() + ";" + entity.getPhoto().getUrl().substring(31);
    }
}
