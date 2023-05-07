package server;

import network.utils.AbstractServer;
import network.utils.ServerException;
import network.utils.UserRpcConcurrentServer;
import repository.ClientRepository;
import repository.ReservationRepository;
import repository.RideRepository;
import repository.UserRepository;
import repository.database.ClientDbRepository;
import repository.database.ReservationDbRepository;
import repository.database.RideDbRepository;
import repository.database.UserDbRepository;

import java.io.IOException;
import java.util.Properties;

public class StartRpcServer {
    public static void main(String[] args) {
        Properties serverProps = getProperties();
        UserServiceServer services = createServices(serverProps);
        int serverPort = Integer.parseInt(serverProps.getProperty("server.port"));
        System.out.println("Starting server on port: " + serverPort);
        AbstractServer server = new UserRpcConcurrentServer(serverPort, services);
        try {
            server.start();
        } catch (ServerException ex) {
            System.err.println("Error starting the server: " + ex.getMessage());
        } finally {
            try {
                server.stop();
            } catch (ServerException ex) {
                System.err.println("Error stopping the server: " + ex.getMessage());
            }
        }
    }

    public static Properties getProperties() {
        Properties serverProps = new Properties();
        try {
            serverProps.load(StartRpcServer.class.getResourceAsStream("/server.properties"));
            System.out.println("Server properties set.");
            serverProps.list(System.out);
        } catch (IOException ex) {
            System.err.println("Cannot find server.properties " + ex);
        }
        return serverProps;
    }

    public static UserServiceServer createServices(Properties props) {
        UserRepository userRepository = new UserDbRepository(props);
        ClientRepository clientRepository = new ClientDbRepository(props);
        RideRepository rideRepository = new RideDbRepository(props);
        ReservationRepository reservationRepository = new ReservationDbRepository(props);
        return new UserServiceServer(userRepository, clientRepository, rideRepository, reservationRepository);
    }
}
