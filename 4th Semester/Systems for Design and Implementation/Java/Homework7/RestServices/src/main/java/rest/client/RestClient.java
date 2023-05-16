package rest.client;

import models.Ride;
import org.springframework.web.client.HttpClientErrorException;
import org.springframework.web.client.ResourceAccessException;
import org.springframework.web.client.RestTemplate;

import java.util.List;
import java.util.concurrent.Callable;

public class RestClient {
    public static final String URL = "http://localhost:8080/api/rides";

    private final RestTemplate restTemplate = new RestTemplate();

    private <T> T execute(Callable<T> callable) {
        try {
            return callable.call();
        } catch (Exception e) { // server down, resource exception
            System.err.println(e.getMessage());
            return null;
        }
    }

    public List<Ride> getRides() {
        return List.of(execute(() -> restTemplate.getForObject(URL, Ride[].class)));
    }

    public Ride getById(String id) {
        return execute(() -> restTemplate.getForObject(String.format("%s/%s", URL, id), Ride.class));
    }

    public Ride create(Ride ride) {
        return execute(() -> restTemplate.postForObject(URL, ride, Ride.class));
    }

    public void update(Ride ride) {
        execute(() -> {
            restTemplate.put(String.format("%s/%s", URL, ride.getID()), ride);
            return null;
        });
    }

    public void delete(String id) {
        execute(() -> {
            restTemplate.delete(String.format("%s/%s", URL, id));
            return null;
        });
    }
}
