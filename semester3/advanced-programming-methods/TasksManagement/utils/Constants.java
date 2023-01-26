package utils;

import java.time.format.DateTimeFormatter;

public class Constants {
    public static final DateTimeFormatter DATE_TIME_FORMATTER
            = DateTimeFormatter.ofPattern("dd-MMM-yyyy HH:mm");
    public static final int INITIAL_CONTAINER_SIZE = 1;
    public static final int CONTAINER_SIZE_MULTIPLIER = 2;
}
