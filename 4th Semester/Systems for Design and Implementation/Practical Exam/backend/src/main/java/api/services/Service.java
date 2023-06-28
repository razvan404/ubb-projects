package api.services;

import api.models.Player;
import api.models.Try;
import api.models.dtos.PlayerScoreDto;
import api.models.dtos.TryResponseDto;
import api.services.exception.ServException;
import api.services.observer.Observer;

import java.util.List;

public interface Service {
    Player login(Player player, Observer observer) throws ServException;
    List<Player> findOnlinePlayers();
    void logout(Observer observer);
    void startGame(Player player) throws ServException;
    TryResponseDto tryWord(Player player, Try tried) throws ServException;
    List<PlayerScoreDto> findLeaderboard();
}
