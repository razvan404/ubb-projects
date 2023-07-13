package api.services.notification;

import java.io.Serializable;

public enum NotificationType implements Serializable {
    PLAYER_LOGGED_IN, PLAYER_LOGGED_OUT, LEADERBOARD_UPDATED
}
