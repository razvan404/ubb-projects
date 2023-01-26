package application.service.exceptions;

/**
 * The class <b>NotFoundException</b> is a Throwable used by the Repositories when an entity doesn't exist in
 * them and the requested operation cannot be completed.
 */
public class NotFoundException extends Exception {
    public NotFoundException(String message) {
        super(message);
    }
}
