package OnwardTravel.gui;

import OnwardTravel.models.User;
import OnwardTravel.repository.UserRepository;
import OnwardTravel.repository.database.UserDbRepository;
import OnwardTravel.repository.exceptions.DataLoadException;
import OnwardTravel.utils.PasswordEncryptor;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class Main {
    public static void main(String[] args) {
        Properties props = new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException ex) {
            System.out.println("Cannot find bd.config " + ex);
            System.out.println(new File(".").getAbsolutePath());
        }
        UserRepository userRepository = new UserDbRepository(props);
        try {
            User user = userRepository.tryLogin("admin", PasswordEncryptor.encrypt("admin"));
            System.out.println(user.getUsername());
        } catch (DataLoadException ex) {
            throw new RuntimeException(ex);
        }
    }
}
