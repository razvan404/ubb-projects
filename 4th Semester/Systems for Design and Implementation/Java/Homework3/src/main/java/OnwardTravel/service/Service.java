package OnwardTravel.service;

import OnwardTravel.models.*;
import OnwardTravel.repository.ClientRepository;
import OnwardTravel.repository.ReservationRepository;
import OnwardTravel.repository.RideRepository;
import OnwardTravel.repository.UserRepository;
import OnwardTravel.repository.exceptions.DataChangeException;
import OnwardTravel.service.exceptions.InvalidDataException;
import OnwardTravel.utils.PasswordEncryptor;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Service {
    private User currentUser;
    private final UserRepository userRepository;
    private final ClientRepository clientRepository;
    private final RideRepository rideRepository;
    private final ReservationRepository reservationRepository;

    private final Logger logger = LogManager.getLogger(Service.class);

    public Service(UserRepository userRepository, ClientRepository clientRepository,
                   RideRepository rideRepository, ReservationRepository reservationRepository) {
        currentUser = null;
        this.userRepository = userRepository;
        this.clientRepository = clientRepository;
        this.rideRepository = rideRepository;
        this.reservationRepository = reservationRepository;
    }

    public void tryLogin(String username, String password) throws InvalidDataException {
        currentUser = userRepository.tryLogin(username, PasswordEncryptor.encrypt(password));
        if (currentUser == null) {
            throw new InvalidDataException("Invalid username or password!");
        }
    }

    public User getCurrentUser() {
        return currentUser;
    }

    public List<Ride> findAllRides() {
        return rideRepository.findAll();
    }

    public int findEmptySeatsOnRide(Ride ride) {
        int occupiedSeatsCount = 0;
        for (Reservation reservation : reservationRepository.findReservationsByRide(ride)) {
            occupiedSeatsCount += reservation.getSeats().size();
        }
        return 18 - occupiedSeatsCount;
    }

    public List<Ride> findRidesByDestinationAndDeparture(String destination, LocalDate departureDay) {
        return rideRepository.findByDestinationAndDeparture(destination, departureDay);
    }

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

    public void createReservation(Ride ride, String clientName, String phoneNumber, int seatsCount) throws InvalidDataException, DataChangeException {
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
            client.setID(clientRepository.save(client));
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
        reservationRepository.save(reservation);
    }
}
