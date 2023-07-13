package api.services.implementation;

import api.models.Player;
import api.persistence.PlayerRepository;
import api.services.Service;
import api.services.exception.ServException;
import api.services.notification.Notification;
import api.services.notification.NotificationType;
import api.services.observer.Observable;
import api.services.observer.Observer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class ServiceImpl extends Observable<Player> implements Service {
    @Autowired
    public PlayerRepository playerRepository;

    @Override
    public Player findByUsernameAndPassword(String username, String password) throws ServException {
        Player player = playerRepository.findByUsernameAndPassword(username, password);
        if (player == null) {
            throw new ServException("Invalid username or password");
        }
        return player;
    }

    @Override
    public Player login(Player player, Observer observer) throws ServException {
        player = playerRepository.findByUsernameAndPassword(player.getUsername(), player.getPassword());
        if (player == null) {
            throw new ServException("Invalid username or password");
        }
        if (observers.containsKey(player)) {
            throw new ServException("Player already logged in");
        }
        addObserver(player, observer);
        notifyObservers(new Notification(NotificationType.PLAYER_LOGGED_IN, player));
        return player;
    }

    @Override
    public List<Player> findOnlinePlayers() {
        return observers.keySet().stream().toList();
    }

    @Override
    public void logout(Observer observer) {
        Player player = removeObserver(observer);
        notifyObservers(new Notification(NotificationType.PLAYER_LOGGED_OUT, player));
    }
}
