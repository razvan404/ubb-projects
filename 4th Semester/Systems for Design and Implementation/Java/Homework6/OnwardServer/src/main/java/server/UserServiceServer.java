package server;

import models.*;
import repository.ClientRepository;
import repository.ReservationRepository;
import repository.RideRepository;
import repository.UserRepository;
import repository.exceptions.DataChangeException;
import service.UserService;
import service.exceptions.InvalidDataException;
import service.observer.UserObservable;
import service.observer.UserObserver;
import utils.PasswordEncryptor;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class UserServiceServer extends UserObservable implements UserService {
    private final UserRepository userRepository;
    private final ClientRepository clientRepository;
    private final RideRepository rideRepository;
    private final ReservationRepository reservationRepository;

    public UserServiceServer(UserRepository userRepository, ClientRepository clientRepository,
                             RideRepository rideRepository, ReservationRepository reservationRepository) {
        this.userRepository = userRepository;
        this.clientRepository = clientRepository;
        this.rideRepository = rideRepository;
        this.reservationRepository = reservationRepository;
    }
    @Override
    public User tryLogin(User user, UserObserver requester) throws InvalidDataException {
        User loggedUser = userRepository.tryLogin(user.getUsername(), user.getPassword());
        if (loggedUser == null) {
            throw new InvalidDataException("Invalid username or password!");
        }
        addObserver(requester);
        return loggedUser;
    }

    @Override
    public void logout(UserObserver requester) {
        removeObserver(requester);
    }

    @Override
    public List<Ride> findAllRides() {
        return rideRepository.findAll();
    }

    @Override
    public int findEmptySeatsOnRide(Ride ride) {
        int occupiedSeatsCount = 0;
        for (Reservation reservation : reservationRepository.findReservationsByRide(ride)) {
            occupiedSeatsCount += reservation.getSeats().size();
        }
        return 18 - occupiedSeatsCount;
    }

    @Override
    public List<Ride> findRidesByDestinationAndDeparture(String destination, LocalDate departureDay) {
        return rideRepository.findByDestinationAndDeparture(destination, departureDay);
    }

    @Override
    public ClientSeat[] findReservationsByRide(Ride ride) {
        ClientSeat[] occupiedSeats = new ClientSeat[18];
        for (Reservation reservation : reservationRepository.findReservationsByRide(ride)) {
            for (ReservedSeat reservedSeat : reservation.getSeats()) {
                occupiedSeats[reservedSeat.getSeatNumber() - 1] =
                        new ClientSeat(reservation.getClient(), reservation, reservedSeat);
            }
        }
        for (int i = 0; i < 18; i++) {
            if (occupiedSeats[i] == null) {
                occupiedSeats[i] =
                        new ClientSeat(null, null, new ReservedSeat(null, i + 1));
            }
        }
        return occupiedSeats;
    }

    @Override
    public void createReservation(Ride ride, String clientName, String phoneNumber, int seatsCount) throws InvalidDataException {
        if (ride == null) {
            throw new InvalidDataException("Cannot create a reservation if there is no ride selected!");
        }
        if (clientName == null || clientName.length() == 0) {
            throw new InvalidDataException("Invalid name!");
        }
        if (phoneNumber == null || phoneNumber.length() == 0) {
            throw new InvalidDataException("Invalid phone number!");
        }
        try {
            Integer.parseInt(phoneNumber);
        } catch (NumberFormatException ignored) {
            throw new InvalidDataException("Invalid phone number!");
        }
        if (seatsCount < 1 || seatsCount > findEmptySeatsOnRide(ride)) {
            throw new InvalidDataException("Invalid number of seats!");
        }

        Client client = clientRepository.findByNameAndPhone(clientName, phoneNumber);
        if (client == null) {
            client = new Client(clientName, phoneNumber);
            try {
                client.setID(clientRepository.save(client));
            } catch (DataChangeException ex) {
                throw new InvalidDataException(ex.getMessage());
            }
        }

        List<ReservedSeat> seatsToReserve = new ArrayList<>();
        for (ClientSeat clientSeat : findReservationsByRide(ride)) {
            if (clientSeat.getClient() == null) {
                seatsToReserve.add(clientSeat.getSeat());
                if (seatsToReserve.size() == seatsCount) {
                    break;
                }
            }
        }

        Reservation reservation = new Reservation(client, ride, seatsToReserve);
        try {
            reservation.setID(reservationRepository.save(reservation));
        } catch (DataChangeException ex) {
            throw new InvalidDataException(ex.getMessage());
        }
        notifyReservationCreated(reservation);
    }
}
