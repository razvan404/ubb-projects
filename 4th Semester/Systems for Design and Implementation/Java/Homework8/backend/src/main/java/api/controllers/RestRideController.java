package api.controllers;

import api.models.Ride;
import api.persistence.hibernate.RideHibernateRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.UUID;

@RestController
@RequestMapping("/api/rides")
public class RestRideController {
    private final RideHibernateRepository rideRepository = new RideHibernateRepository();

    @CrossOrigin
    @RequestMapping(method = RequestMethod.GET)
    public List<Ride> getRides(){
        System.out.println("Get all rides ...");
        return rideRepository.findAll();
    }

    @CrossOrigin
    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<Ride> getById(@PathVariable UUID id){
        Ride ride = rideRepository.find(id);
        if (ride == null) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(ride);
    }

    @CrossOrigin
    @RequestMapping(method = RequestMethod.POST)
    public ResponseEntity<Ride> create(@RequestBody Ride ride) {
        if (rideRepository.save(ride) == null) {
            return ResponseEntity.badRequest().build();
        }
        return ResponseEntity.ok(ride);
    }

    @CrossOrigin
    @RequestMapping(value = "/{id}", method = RequestMethod.PUT)
    public ResponseEntity<Ride> update(@PathVariable UUID id, @RequestBody Ride ride) {
        ride.setID(id);
        if (rideRepository.find(id) == null) {
            return ResponseEntity.notFound().build();
        }
        rideRepository.update(ride);
        return ResponseEntity.ok(ride);
    }

    @CrossOrigin
    @RequestMapping(value = "/{id}", method= RequestMethod.DELETE)
    public ResponseEntity<Ride> delete(@PathVariable UUID id){
        System.out.println("Deleting ride ... " + id);
        if (rideRepository.find(id) == null) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(rideRepository.delete(id));
    }

    @CrossOrigin
    @RequestMapping(value = "/{id}/destination", method = RequestMethod.GET)
    public String getDestination(@PathVariable String id){
        System.out.println("Get destination by id ... " + id);
        return rideRepository.find(UUID.fromString(id)).getDestination();
    }
}
