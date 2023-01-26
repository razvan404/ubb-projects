package application.models;

import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * The class <b>Community</b> represents an undirected connected graph for the users of the application, based on their friendships.
 */
public class Community {
    /**
     * The minimum numbers of members a community should have.
     */
    public final static short MINIMUM_MEMBERS = 2;
    private final List<User> userList;
    private final int socialScore;
    private final double ageAverage;
    private final int friendshipsCount;

    /**
     * Class constructor for the Community.
     * @param userList the list of users in the community
     * @param uuidGraph a map with uuid keys and list of uuid values, representing the lists of adjacency in the graph of the community
     */
    public Community(List<User> userList, Map<UUID, List<UUID>> uuidGraph) {
        this.userList = userList;

        ageAverage = ((int) (userList.stream().mapToDouble(user -> (double) user.getAge())
                .average().orElse(0) * 100)) / 100d;

        final AtomicInteger vertices = new AtomicInteger(0);
        uuidGraph.keySet().forEach(user -> vertices.addAndGet(uuidGraph.get(user).size()));
        friendshipsCount = vertices.get() / 2;

        final AtomicInteger maxDistance = new AtomicInteger(0);
        uuidGraph.keySet().forEach(user -> {
            Set<UUID> visited = new HashSet<>();
            visited.add(user);
            int distance = longestPathFromNode(uuidGraph, user, visited);
            maxDistance.set(Math.max(maxDistance.get(), distance));
        });
        socialScore = maxDistance.get();
    }

    /**
     * Calculates the distance of the longest path from a given node in the community.
     * @param current the current node in the community graph
     * @return the distance of the longest path from the current node to any unvisited node in the community graph
     */
    private int longestPathFromNode(Map<UUID, List<UUID>> uuidGraph, UUID current, Set<UUID> visited) {
        AtomicInteger maxDistance = new AtomicInteger(1);
        uuidGraph.get(current).forEach(friend -> {
            if (!visited.contains(friend)) {
                visited.add(friend);
                int distance = longestPathFromNode(uuidGraph, friend, visited) + 1;
                visited.remove(friend);
                maxDistance.set(Math.max(maxDistance.get(), distance));
            }
        });
        return maxDistance.get();
    }

    /**
     * @return the members of the Community
     */
    public List<User> getUserList() {
        return userList;
    }

    /**
     * @return the average of the ages of the community members
     */
    public double getAgeAverage() {
        return ageAverage;
    }

    /**
     * @return the social score of a community
     */
    public int getSocialScore() {
        return socialScore;
    }

    /**
     * @return the number of friendships in the community
     */
    public int getFriendshipsCount() {
        return friendshipsCount;
    }
}