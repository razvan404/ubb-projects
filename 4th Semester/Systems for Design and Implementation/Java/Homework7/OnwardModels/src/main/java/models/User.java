package models;

import utils.PasswordEncryptor;

import java.util.UUID;

import javax.persistence.*;

@Entity
@Table(name = "users")
public class User extends Identifiable<UUID> {
    private String username;
    private String password;

    public User() {}

    public User(UUID identifier, String username, String password) {
        super(identifier);
        this.username = username;
        this.password = password;
    }

    public User(String username, String password) {
        this.username = username;
        this.password = PasswordEncryptor.encrypt(password);
    }

    @Override
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "user_id", updatable = false, nullable = false)
    public UUID getID() {
        return super.getID();
    }

    public void setID(UUID id) {
        super.setID(id);
    }

    @Column(name = "username")
    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    @Column(name = "password")
    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
