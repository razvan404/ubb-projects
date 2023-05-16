package start;

import models.Ride;
import rest.client.RestClient;

import java.time.LocalDateTime;

public class StartRestClient {
    public static final RestClient restClient = new RestClient();
    public static void main(String[] args) {
        System.out.println("======================================================");
        System.out.println("List of Rides");
        restClient.getRides().forEach(System.out::println);

        System.out.println("======================================================");
        System.out.println("Creating a Ride");
        Ride newRide = new Ride("Chinteni", LocalDateTime.now());
        newRide = restClient.create(newRide);

        System.out.println("======================================================");
        System.out.println("Created Ride");
        System.out.println(restClient.getById(newRide.getID().toString()));

        System.out.println("======================================================");
        System.out.println("Updating a Ride");
        newRide.setDestination("Cluj-Napoca");
        restClient.update(newRide);

        System.out.println("======================================================");
        System.out.println("Updated Ride");
        System.out.println(restClient.getById(newRide.getID().toString()));

        System.out.println("======================================================");
        System.out.println("Deleting a Ride");
        restClient.delete(newRide.getID().toString());

        System.out.println("======================================================");
        System.out.println("Deleted Ride");
        System.out.println(restClient.getById(newRide.getID().toString()));
    }

    private static void show(Runnable task) {
        try {
            task.run();
        } catch (RuntimeException e) {
            System.out.println("Exception " + e);
        }
    }
}
