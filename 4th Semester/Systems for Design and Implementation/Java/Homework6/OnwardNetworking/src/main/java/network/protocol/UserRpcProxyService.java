package network.protocol;

import models.ClientSeat;
import models.Reservation;
import models.Ride;
import models.User;
import network.dto.ReservationInfoDTO;
import network.dto.RideInfoDTO;
import service.UserService;
import service.exceptions.InvalidDataException;
import service.observer.UserObserver;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.time.LocalDate;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class UserRpcProxyService implements UserService {
    private final String host;
    private final int port;

    private UserObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private final BlockingQueue<Response> responses;
    private volatile boolean finished;

    public UserRpcProxyService(String host, int port) {
        this.host = host;
        this.port = port;
        responses = new LinkedBlockingDeque<>();
    }

    private class ReaderThread implements Runnable {
        private boolean isUpdate(Response response) {
            return response.getType() == ResponseType.RESERVATION_CREATED;
        }

        private void handleUpdate(Response response) {
            if (response.getType() == ResponseType.RESERVATION_CREATED) {
                Reservation reservation = (Reservation) response.getData();
                client.handleReservationCreated(reservation);
            }
        }

        @Override
        public void run() {
            while (!finished) {
                try {
                    Response response = (Response) input.readObject();
                    if (isUpdate(response)) {
                        handleUpdate(response);
                    } else {
                        responses.put(response);
                    }
                } catch (SocketException ignored) {
                } catch (IOException | ClassNotFoundException | InterruptedException ex) {
                    ex.printStackTrace();
                }
            }
        }
    }

    private void startReader() {
        new Thread(new ReaderThread()).start();
    }

    private void initConnection() {
        try {
            connection = new Socket(host, port);
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            finished = false;
            startReader();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void closeConnection() {
        finished = true;
        try {
            input.close();
            output.close();
            connection.close();
            client = null;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void sendRequest(Request request) {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private Response readResponse() {
        Response response = null;
        try {
            response = responses.take();
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
        return response;
    }

    @Override
    public User tryLogin(User user, UserObserver requester) throws InvalidDataException {
        initConnection();

        Request request = new Request.Builder().setType(RequestType.LOGIN).setData(user).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.getType() == ResponseType.OK) {
            client = requester;
            return (User) response.getData();
        }
        else {
            String err = response.getData().toString();
            closeConnection();
            throw new InvalidDataException(err);
        }
    }

    @Override
    public void logout(UserObserver requester) {
        Request request = new Request.Builder().setType(RequestType.LOGOUT).build();
        sendRequest(request);
        readResponse();
        closeConnection();
    }

    @Override
    public List<Ride> findAllRides() {
        Request request = new Request.Builder().setType(RequestType.FIND_RIDES).build();
        sendRequest(request);
        Response response = readResponse();
        return (List<Ride>) response.getData();
    }

    @Override
    public int findEmptySeatsOnRide(Ride ride) {
        Request request = new Request.Builder().setType(RequestType.FIND_EMPTY_SEATS_ON_RIDE).setData(ride).build();
        sendRequest(request);
        Response response = readResponse();
        return (int) response.getData();
    }

    @Override
    public List<Ride> findRidesByDestinationAndDeparture(String destination, LocalDate departureDay) {
        RideInfoDTO info = new RideInfoDTO(destination, departureDay);
        Request request = new Request.Builder().setType(RequestType.FIND_RIDES_BY_DEST_AND_DEPART).setData(info).build();
        sendRequest(request);
        Response response = readResponse();
        return (List<Ride>) response.getData();
    }

    @Override
    public ClientSeat[] findReservationsByRide(Ride ride) {
        Request request = new Request.Builder().setType(RequestType.FIND_RESERVATIONS_BY_RIDE).setData(ride).build();
        sendRequest(request);
        Response response = readResponse();
        return (ClientSeat[]) response.getData();
    }

    @Override
    public void createReservation(Ride ride, String clientName, String phoneNumber, int seatsCount) throws InvalidDataException {
        ReservationInfoDTO info = new ReservationInfoDTO(ride, clientName, phoneNumber, seatsCount);
        Request request = new Request.Builder().setType(RequestType.CREATE_RESERVATION).setData(info).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.getType() == ResponseType.ERROR) {
            throw new InvalidDataException(response.getData().toString());
        }
    }
}
