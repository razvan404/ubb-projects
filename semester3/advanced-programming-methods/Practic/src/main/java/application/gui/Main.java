package application.gui;

import application.controller.ClientViewController;
import application.controller.MainViewController;
import application.repository.*;
import application.service.Service;
import application.utils.Config;
import application.utils.DataBase;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    private static final DataBase dataBase = new DataBase(
            Config.getProperty("database_url"),
            Config.getProperty("database_username"),
            Config.getProperty("database_password"));

    private static final Service service = new Service(
            new LocationRepository(dataBase),
            new HotelRepository(dataBase),
            new SpecialOfferRepository(dataBase),
            new ClientRepository(dataBase),
            new ReservationRepository(dataBase));

    private static String[] arguments;

    @Override
    public void start(Stage stage) throws IOException {

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-view.fxml"));
        AnchorPane mainPane = fxmlLoader.load();
        fxmlLoader.<MainViewController>getController().setService(service);
        fxmlLoader.<MainViewController>getController().build();
        Scene scene = new Scene(mainPane, 400, 600);
        stage.setTitle("Hotels management");
        stage.setScene(scene);
        stage.show();
        for (var arg : arguments) {
            Stage clientStage = new Stage();
            FXMLLoader loader = new FXMLLoader(Main.class.getResource("client-view.fxml"));
            AnchorPane clientPane = loader.load();
            loader.<ClientViewController>getController()
                    .setResources(service, service.getClient(Long.parseLong(arg)));
            loader.<ClientViewController>getController().build();
            Scene clientScene = new Scene(clientPane, 400, 600);
            clientStage.setTitle("Client page");
            clientStage.setScene(clientScene);
            clientStage.show();
        }
    }

    public static void main(String[] args) {
        arguments = args;
        launch();
    }
}