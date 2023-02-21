package application.models.exceptions;

/**
 * The throwable class <b>ValidationException</b> is thrown when an entity is not valid.
 */
public class ValidationException extends Exception {
    public ValidationException(String message) {
        super(message);
    }

}
