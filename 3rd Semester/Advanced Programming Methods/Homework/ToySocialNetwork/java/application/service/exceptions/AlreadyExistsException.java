package application.service.exceptions;

/**
 * The class <b>AlreadyExistsException</b> is a Throwable used by the Repositories when an entity already exists in
 * them and the requested operation cannot be completed.
 */
public class AlreadyExistsException extends Exception {
    public AlreadyExistsException(String message) {
        super(message);
    }
}
