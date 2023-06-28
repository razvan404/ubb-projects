package api.services;

import api.models.Player;
import api.services.exception.ServException;
import api.services.observer.Observer;

import java.util.List;

public interface Service {
    Player findByUsernameAndPassword(String username, String password) throws ServException;
    Player login(Player player, Observer observer) throws ServException;
    List<Player> findOnlinePlayers();
    void logout(Observer observer);
}
