package gui;

import ams.RidesController;
import controllers.RidesView;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import java.io.IOException;

public class ClientStartGUI extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("spring-client.xml");
        RidesController ctrl = context.getBean("ridesCtrl", RidesController.class);

        FXMLLoader fxmlLoader = new FXMLLoader(ClientStartGUI.class.getResource("rides-view.fxml"));
        AnchorPane anchorPane = fxmlLoader.load();
        fxmlLoader.<RidesView>getController().setController(ctrl);
        Scene scene = new Scene(anchorPane, 800, 600);
        stage.setTitle("Rides management");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}