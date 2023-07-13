package api.controllers;

import api.models.Identifiable;
import api.persistence.CrudRepository;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.io.Serializable;
import java.util.List;

public abstract class AbsRestController<ID extends Serializable, E extends Identifiable<ID>> {

    protected CrudRepository<ID, E> repository;
    public AbsRestController(CrudRepository<ID, E> repository) {
        this.repository = repository;
    }

    @GetMapping
    public List<E> findAll() {
        return repository.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<?> findById(@PathVariable ID id) {
        E entity = repository.findOne(id);
        if (entity == null) {
            return new ResponseEntity<>("The entity was not found!", HttpStatus.NOT_FOUND);
        }
        return new ResponseEntity<>(entity, HttpStatus.OK);
    }

    @PostMapping
    public ResponseEntity<?> save(@RequestBody E entity) {
        entity = repository.save(entity);
        if (entity == null) {
            return new ResponseEntity<>("The entity was not saved!", HttpStatus.BAD_REQUEST);
        }
        return new ResponseEntity<>(entity, HttpStatus.OK);
    }

    @PutMapping("/{id}")
    public ResponseEntity<?> update(@PathVariable ID id, @RequestBody E entity) {
        entity.setId(id);
        entity = repository.update(entity);
        if (entity == null) {
            return new ResponseEntity<>("The entity was not updated!", HttpStatus.BAD_REQUEST);
        }
        return new ResponseEntity<>(entity, HttpStatus.OK);
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<?> delete(@PathVariable ID id) {
        E entity = repository.delete(id);
        if (entity == null) {
            return new ResponseEntity<>("The entity was not deleted!", HttpStatus.BAD_REQUEST);
        }
        return new ResponseEntity<>(entity, HttpStatus.OK);
    }
}
