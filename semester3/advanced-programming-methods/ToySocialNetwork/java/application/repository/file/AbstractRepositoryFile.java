package application.repository.file;

import application.models.Entity;
import application.repository.memory.AbstractRepositoryInMemory;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * The abstract class <b>FileRepository</b> contains CRUD operations with the data stored in files.
 * @param <ID> the identifier of the Entity
 * @param <E> the type of Element, should extend Entity
 */
public abstract class AbstractRepositoryFile<ID, E extends Entity<ID>> extends AbstractRepositoryInMemory<ID, E> {
    private final Path path;

    /**
     * Constructs a new FileRepository.
     * @param fileName the file where the data will be stored
     */
    public AbstractRepositoryFile(String fileName) {
        this.path = Paths.get(fileName);
        loadData();
    }

    /**
     * Extracts the data from the file and converts it into an Entity.
     */
    private void loadData() {
        try {
            Files.readAllLines(path).forEach(line -> super.save(extractEntity(List.of(line.split(";")))));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Writes the data to the file.
     */
    private void writeData() {
        try {
            List<CharSequence> stringList = new ArrayList<>();
            super.findAll().forEach(entity -> stringList.add(entityAsString(entity)));
            Files.write(path, String.join("\n", stringList).getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<E> save(E entity) throws IllegalArgumentException {
        Optional<E> unsavedEntity = super.save(entity);
        if (unsavedEntity.isEmpty()) {
            writeData();
        }
        return unsavedEntity;
    }

    @Override
    public Optional<E> delete(ID id) throws IllegalArgumentException {
        Optional<E> entity = super.delete(id);
        if (entity.isPresent()) {
            writeData();
        }
        return entity;

    }

    @Override
    public Optional<E> update(E entity) throws IllegalArgumentException {
        Optional<E> oldEntity = super.update(entity);
        if (oldEntity.isPresent()) {
            writeData();
        }
        return oldEntity;
    }

    /**
     * Extracts an Entity from the list of the attributes.
     * @param attributes the details about the Entity
     * @return the Entity created from the attributes
     */
    protected abstract E extractEntity(List<String> attributes);

    /**
     * Converts an Entity to a string, respecting the file reading format.
     * @param entity the Entity to convert into a String
     * @return the String respecting the file reading format
     */
    protected abstract String entityAsString(E entity);
}
