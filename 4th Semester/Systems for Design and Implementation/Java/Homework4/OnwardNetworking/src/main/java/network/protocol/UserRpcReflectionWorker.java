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
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.util.List;

public class UserRpcReflectionWorker implements Runnable, UserObserver {
    private final UserService service;
    private ObjectInputStream input;
    private ObjectOutputStream output;

    private volatile boolean connected;

    public UserRpcReflectionWorker(UserService service, Socket connection) {
        this.service = service;
        try {
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            connected = true;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    public void run() {
        while (connected) {
            try {
                Object request = input.readObject();
                Response response = handleRequest((Request) request);
                if (response != null) {
                    sendResponse(response);
                }
            } catch (IOException | ClassNotFoundException ex) {
                ex.printStackTrace();
                connected = false;
            }
        }
    }

    private Response handleRequest(Request request) {
        Response response = null;
        String handlerName = "handle" + request.getType();
        try {
            Method method = getClass().getDeclaredMethod(handlerName, Request.class);
            response = (Response) method.invoke(this, request);
        } catch (InvocationTargetException | NoSuchMethodException | IllegalAccessException ex) {
            ex.printStackTrace();
        }
        return response;
    }

    private Response handleLOGIN(Request request) {
        User user = (User) request.getData();
        try {
            service.tryLogin(user, this);
            return new Response.Builder().setType(ResponseType.OK).setData(user).build();
        } catch (InvalidDataException ex) {
            connected = false;
            return new Response.Builder().setType(ResponseType.ERROR).setData(ex.getMessage()).build();
        }
    }

    private Response handleLOGOUT(Request request) {
        service.logout(this);
        connected = false;
        return new Response.Builder().setType(ResponseType.OK).build();
    }

    private Response handleFIND_RIDES(Request request) {
        List<Ride> rides = service.findAllRides();
        return new Response.Builder().setType(ResponseType.OK).setData(rides).build();
    }

    private Response handleFIND_EMPTY_SEATS_ON_RIDE(Request request) {
        int emptySeats = service.findEmptySeatsOnRide((Ride) request.getData());
        return new Response.Builder().setType(ResponseType.OK).setData(emptySeats).build();
    }

    private Response handleFIND_RIDES_BY_DEST_AND_DEPART(Request request) {
        RideInfoDTO info = (RideInfoDTO) request.getData();
        List<Ride> rides = service.findRidesByDestinationAndDeparture(info.destination(), info.departure());
        return new Response.Builder().setType(ResponseType.OK).setData(rides).build();
    }

    private Response handleFIND_RESERVATIONS_BY_RIDE(Request request) {
        ClientSeat[] clientSeats = service.findReservationsByRide((Ride) request.getData());
        return new Response.Builder().setType(ResponseType.OK).setData(clientSeats).build();
    }

    private Response handleCREATE_RESERVATION(Request request) {
        try {
            ReservationInfoDTO info = (ReservationInfoDTO) request.getData();
            service.createReservation(info.ride(), info.clientName(), info.phoneNumber(), info.seatsCount());
            return new Response.Builder().setType(ResponseType.OK).build();
        } catch (InvalidDataException ex) {
            String err = ex.getMessage();
            return new Response.Builder().setType(ResponseType.ERROR).setData(err).build();
        }
    }

    private void sendResponse(Response response) throws IOException {
        output.writeObject(response);
        output.flush();
    }

    @Override
    public void handleReservationCreated(Reservation reservation) {
        Response response = new Response.Builder().setType(ResponseType.RESERVATION_CREATED).setData(reservation).build();
        try {
            sendResponse(response);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}
