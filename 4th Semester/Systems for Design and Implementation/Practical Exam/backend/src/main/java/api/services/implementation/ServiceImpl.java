package api.services.implementation;

import api.models.Game;
import api.models.Player;
import api.models.Try;
import api.models.Word;
import api.models.dtos.PlayerScoreDto;
import api.models.dtos.TryResponseDto;
import api.persistence.GameRepository;
import api.persistence.PlayerRepository;
import api.persistence.TryRepository;
import api.persistence.WordRepository;
import api.services.Service;
import api.services.exception.ServException;
import api.services.notification.Notification;
import api.services.notification.NotificationType;
import api.services.observer.Observable;
import api.services.observer.Observer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

@Component
public class ServiceImpl extends Observable<Player> implements Service {
    @Autowired
    public PlayerRepository playerRepository;
    @Autowired
    public GameRepository gameRepository;
    @Autowired
    public WordRepository wordRepository;
    @Autowired
    public TryRepository tryRepository;

    @Override
    public Player login(Player player, Observer observer) throws ServException {
        player = playerRepository.findByAlias(player.getAlias());
        if (player == null) {
            throw new ServException("Invalid alias!");
        }
        if (observers.containsKey(player)) {
            throw new ServException("Player already logged in!");
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

    @Override
    public void startGame(Player player) throws ServException {
        Game game = new Game();
        game.setPlayer(player);
        List<Word> words = wordRepository.findAll();
        Collections.shuffle(words);
        System.out.println("Ajung aici!1");
        List<Word> words2 = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            words2.add(words.get(i));
        }
        words = words2;
        for (int i = 0; i < 5; i++) {
            words.add(words.get(i));
        }
        System.out.println("Ajung aici!2");
        Collections.shuffle(words);
        game.setConfiguration(words);
        game = gameRepository.save(game);
        if (game == null) {
            throw new ServException("Could not start game!");
        }
    }

    @Override
    public TryResponseDto tryWord(Player player, Try tried) throws ServException {
        Game game = gameRepository.findUnfinishedGameFrom(player);
        if (game == null) {
            throw new ServException("No game in progress!");
        }
        if (game.getTries().size() >= 10) {
            throw new ServException("No more tries allowed, limit 10 hit!");
        }
        if (game.getTries().contains(tried)) {
            throw new ServException("Combination already tried!");
        }
        tried.setGameId(game.getId());
        tryRepository.save(tried);
        game.getTries().add(tried);
        boolean success = game.getConfiguration().get(tried.getWord1idx()).getWord()
                .equals(game.getConfiguration().get(tried.getWord2idx()).getWord());
        if (success) {
            game.setScore(game.getScore() - 2);
        }
        else {
            game.setScore(game.getScore() + 3);
        }
        int correctTries = 0;
        for (Try t : game.getTries()) {
            if (game.getConfiguration().get(t.getWord1idx()).getWord()
                    .equals(game.getConfiguration().get(t.getWord2idx()).getWord())) {
                correctTries++;
            }
        }
        boolean finished = game.getTries().size() == 10 || correctTries == 5;
        if (finished) {
            game.setFinishedAt(LocalDateTime.now());
            notifyObservers(new Notification(NotificationType.LEADERBOARD_UPDATED, game));
        }
        gameRepository.update(game);
        return new TryResponseDto(tried.getWord1idx(), game.getConfiguration().get(tried.getWord1idx()).getWord(),
                tried.getWord2idx(), game.getConfiguration().get(tried.getWord2idx()).getWord(), finished);
    }

    @Override
    public List<PlayerScoreDto> findLeaderboard() {
        return gameRepository.findLeaderboard().stream()
                .map(game -> new PlayerScoreDto(game.getPlayer().getId(), game.getPlayer().getAlias(), game.getScore(),
                        ChronoUnit.SECONDS.between(game.getStartedAt(), game.getFinishedAt())))
                .toList();
    }
}
