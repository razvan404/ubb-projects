package models;

import utils.PasswordEncryptor;

import java.util.UUID;

public class User extends Entity<UUID> {
    private final String username;
    private final String password;

    public User(UUID identifier, String username, String password) {
        super(identifier);
        this.username = username;
        this.password = password;
    }

    public User(String username, String password) {
        this.username = username;
        this.password = PasswordEncryptor.encrypt(password);
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }
}
