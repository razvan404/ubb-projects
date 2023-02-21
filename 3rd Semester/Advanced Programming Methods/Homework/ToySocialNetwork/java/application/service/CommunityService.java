package application.service;

import application.models.Community;
import application.repository.CommunityRepository;

import java.util.*;

public class CommunityService {
    private final CommunityRepository repository;

    public CommunityService(CommunityRepository repository) {
        this.repository = repository;
    }

    public Community findCommunityFrom(UUID user) {
        return repository.extractCommunityFrom(user).orElse(null);
    }
}
