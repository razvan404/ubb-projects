package network.utils;

import network.protocol.UserRpcReflectionWorker;
import service.UserService;

import java.net.Socket;

public class UserRpcConcurrentServer extends AbstractConcurrentServer {
    private final UserService userService;

    public UserRpcConcurrentServer(int port, UserService userService) {
        super(port);
        this.userService = userService;
    }

    @Override
    protected Thread createWorker(Socket client) {
        Runnable worker = new UserRpcReflectionWorker(userService, client);
        return new Thread(worker);
    }
}
