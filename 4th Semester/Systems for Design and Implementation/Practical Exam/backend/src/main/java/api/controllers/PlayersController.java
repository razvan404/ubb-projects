package api.controllers;


import api.models.Player;
import api.persistence.PlayerRepository;
import api.services.Service;
import api.services.exception.ServException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.UUID;

@RestController
@CrossOrigin
@RequestMapping("/api/players")
public class PlayersController extends AbsRestController<UUID, Player> {
    public PlayersController(@Autowired PlayerRepository repository) {
        super(repository);
    }
}
