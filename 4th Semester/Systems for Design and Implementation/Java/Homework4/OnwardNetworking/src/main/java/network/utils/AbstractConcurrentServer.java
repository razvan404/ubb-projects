package network.utils;

import java.net.Socket;

public abstract class AbstractConcurrentServer extends AbstractServer {
    public AbstractConcurrentServer(int port) {
        super(port);
    }

    @Override
    protected void processRequest(Socket client) {
        Thread tw = createWorker(client);
        tw.start();
    }

    protected abstract Thread createWorker(Socket client);
}
