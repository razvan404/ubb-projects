package networking.utils;

import networking.protocol.AMSReflectionWorker;
import services.ServicesAMS;

import java.net.Socket;

public class AMSConcurrentServer extends AbsConcurrentServer {
    private final ServicesAMS server;
    public AMSConcurrentServer(int port, ServicesAMS server) {
        super(port);
        this.server = server;
        System.out.println("AMSConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        AMSReflectionWorker worker = new AMSReflectionWorker(server, client);
        return new Thread(worker);
    }
}
