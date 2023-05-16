package api.services.rest;

import models.Ride;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import repository.exceptions.DataChangeException;
import repository.hibernate.RideHibernateRepository;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

@RestController
@RequestMapping("/api/rides")
public class RestRideController {
    private final RideHibernateRepository rideRepository = new RideHibernateRepository();

    @RequestMapping(method = RequestMethod.GET)
    public List<Ride> getRides(){
        System.out.println("Get all rides ...");
        return rideRepository.findAll();
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<Ride> getById(@PathVariable UUID id){
        Ride ride = rideRepository.find(id);
        if (ride == null) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(ride);
    }

    @RequestMapping(method = RequestMethod.POST)
    public ResponseEntity<Ride> create(@RequestBody Ride ride){
        try {
            rideRepository.save(ride);
            return ResponseEntity.ok(ride);
        } catch (DataChangeException ex) {
            return ResponseEntity.badRequest().build();
        }
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.PUT)
    public ResponseEntity<Ride> update(@PathVariable UUID id, @RequestBody Ride ride) {
        ride.setID(id);
        if (rideRepository.find(id) == null) {
            return ResponseEntity.notFound().build();
        }
        rideRepository.update(ride);
        return ResponseEntity.ok(ride);
    }

    @RequestMapping(value = "/{id}", method= RequestMethod.DELETE)
    public ResponseEntity<Ride> delete(@PathVariable UUID id){
        System.out.println("Deleting ride ... "+id);
        if (rideRepository.find(id) == null) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(rideRepository.delete(id));
    }

    @RequestMapping(value = "/{id}/destination", method = RequestMethod.GET)
    public String getDestination(@PathVariable String id){
        System.out.println("Get destination by id " + id);
        return rideRepository.find(UUID.fromString(id)).getDestination();
    }
}
