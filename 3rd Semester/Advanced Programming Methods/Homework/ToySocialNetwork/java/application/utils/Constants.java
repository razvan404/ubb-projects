package application.utils;

import javafx.scene.image.Image;

import java.time.format.DateTimeFormatter;
import java.util.UUID;

/**
 * The class <b>Constants</b> contains different constants used in the application.
 */
public class Constants {
    public static DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("dd.MM.yyyy");
    public static DateTimeFormatter TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm");
    public static DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ofPattern("dd MMMM yyyy, HH:mm");
    public static UUID SERVER_UUID = UUID.fromString("00000000-0000-0000-0000-000000000000");
    public static Image APP_ICON = new Image("/application/gui/media/logo.png");
}
