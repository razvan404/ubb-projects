package OnwardTravel.gui;

import OnwardTravel.controller.ControllerUtils;
import OnwardTravel.repository.ClientRepository;
import OnwardTravel.repository.ReservationRepository;
import OnwardTravel.repository.RideRepository;
import OnwardTravel.repository.UserRepository;
import OnwardTravel.repository.database.ClientDbRepository;
import OnwardTravel.repository.database.ReservationDbRepository;
import OnwardTravel.repository.database.RideDbRepository;
import OnwardTravel.repository.database.UserDbRepository;
import OnwardTravel.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class OnwardTravel extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        ControllerUtils.setService(getNewService(getProperties()));
        ControllerUtils.setStage(stage);

        FXMLLoader fxmlLoader = new FXMLLoader(OnwardTravel.class.getResource("login-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 800, 600);
        stage.setTitle("Onward Travel");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }

    public static Properties getProperties() {
        Properties props = new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException ex) {
            System.err.println("Invalid properties path: " + new File(".").getAbsolutePath());
            throw new RuntimeException("Cannot load bd.config!");
        }
        return props;
    }

    public Service getNewService(Properties props) {
        UserRepository userRepository = new UserDbRepository(props);
        ClientRepository clientRepository = new ClientDbRepository(props);
        RideRepository rideRepository = new RideDbRepository(props);
        ReservationRepository reservationRepository = new ReservationDbRepository(props);
        return new Service(userRepository, clientRepository, rideRepository, reservationRepository);
    }
}