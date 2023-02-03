package application.service;

import application.models.*;
import application.models.exceptions.ValidationException;
import application.repository.*;
import application.utils.observer.Observable;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.List;

public class Service extends Observable {
    private final LocationRepository locationRepository;
    private final HotelRepository hotelRepository;
    private final SpecialOfferRepository specialOfferRepository;
    private final ClientRepository clientRepository;
    private final ReservationRepository reservationRepository;

    public Service(LocationRepository locationRepository, HotelRepository hotelRepository, SpecialOfferRepository specialOfferRepository, ClientRepository clientRepository, ReservationRepository reservationRepository) {
        this.locationRepository = locationRepository;
        this.hotelRepository = hotelRepository;
        this.specialOfferRepository = specialOfferRepository;
        this.clientRepository = clientRepository;
        this.reservationRepository = reservationRepository;
    }

    public List<Location> getLocations() {
        return  locationRepository.findAll();
    }

    public List<Hotel> getHotels() {
        return hotelRepository.findAll();
    }

    public List<Hotel> getHotelsFrom(Location location) {
        return hotelRepository.findHotelsFrom(location.getID());
    }

    public List<SpecialOffer> getSpecialOffersFrom(Hotel hotel) {
        return specialOfferRepository.findAllFrom(hotel.getID());
    }

    public List<SpecialOffer> getSpecialOffersBetween(Hotel hotel, LocalDate startDate, LocalDate endDate) throws ValidationException {
        if (startDate == null || endDate == null) {
            throw new ValidationException("You should introduce both the dates!");
        }
        if (startDate.isAfter(endDate)) {
            throw new ValidationException("The end date should be later than the start date!");
        }
        return getSpecialOffersFrom(hotel).stream()
                .filter(specialOffer -> (startDate.isAfter(specialOffer.getStartDate()) ||
                        startDate.isEqual(specialOffer.getStartDate()))
                        && (endDate.isBefore(specialOffer.getEndDate()) ||
                        endDate.isEqual(specialOffer.getEndDate())))
                .toList();
    }

    public Client getClient(long id) {
        return clientRepository.find(id)
                .orElseThrow(() -> new IllegalArgumentException("Invalid client identifier!"));
    }

    public List<SpecialOffer> getClientSpecialOffers(Client client) {
        return specialOfferRepository.findAllWithPercentsLowerThan(client.getFidelityGrade());
    }

    public Hotel getHotel(double id) {
        return hotelRepository.find(id)
                .orElseThrow(() -> new IllegalArgumentException("Invalid hotel identifier!"));
    }

    public void reserve(Client client, Hotel hotel, LocalDateTime startDate, int noNights) throws ValidationException {
        reservationRepository.save(Reservation.create(client, hotel, startDate, noNights));
        notifyObservers(client, hotel);
    }
}