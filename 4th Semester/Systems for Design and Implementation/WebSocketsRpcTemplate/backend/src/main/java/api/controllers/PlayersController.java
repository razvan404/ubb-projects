package api.controllers;


import api.models.Player;
import api.persistence.PlayerRepository;
import api.services.Service;
import api.services.exception.ServException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin
@RequestMapping("/api/players")
public class PlayersController {
    @Autowired
    private Service service;
    @Autowired
    private PlayerRepository playerRepository;

    @PostMapping
    public ResponseEntity<Player> save(@RequestBody Player player) {
         player = playerRepository.save(player);
         if (player == null) {
             return ResponseEntity.badRequest().build();
         }
         return ResponseEntity.ok(player);
    }

    @GetMapping
    public List<Player> findAll(@RequestParam(required = false) boolean online) {
        if (online) {
            return service.findOnlinePlayers();
        }
        return playerRepository.findAll();
    }
}
