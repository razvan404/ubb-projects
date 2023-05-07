package network.utils;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public abstract class AbstractServer {
    private final int port;
    private ServerSocket server = null;

    public AbstractServer(int port) {
        this.port = port;
    }

    public void start() throws ServerException {
        try {
            server = new ServerSocket(port);
            while (true) {
                Socket client = server.accept();
                processRequest(client);
            }
        } catch (IOException ex) {
            throw new ServerException("Starting server error: ", ex);
        }
    }

    protected abstract void processRequest(Socket client);

    public void stop() throws ServerException {
        try {
            server.close();
        } catch (IOException ex) {
            throw new ServerException("Closing server error: ", ex);
        }
    }
}
