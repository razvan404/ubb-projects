package api.controllers;

import api.models.Game;
import api.persistence.GameRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Collections;
import java.util.UUID;

@RestController
@CrossOrigin
@RequestMapping("/api/games")
public class GameController extends AbsRestController<UUID, Game> {
    public GameController(@Autowired GameRepository repository) {
        super(repository);
    }

    @PutMapping("/{id}/shuffle")
    public ResponseEntity<?> update(@PathVariable UUID id) {
        Game game = repository.findOne(id);
        if (game == null) {
            return new ResponseEntity<>("The entity was not found!", HttpStatus.NOT_FOUND);
        }
        Collections.shuffle(game.getConfiguration());
        repository.update(game);
        return new ResponseEntity<>(game, HttpStatus.OK);
    }
}
