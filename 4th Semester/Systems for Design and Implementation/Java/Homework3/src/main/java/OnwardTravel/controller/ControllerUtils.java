package OnwardTravel.controller;

import OnwardTravel.service.Service;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.stage.Stage;

public class ControllerUtils {
    private static Service service = null;
    private static Stage stage;



    public static void setService(Service service) {
        ControllerUtils.service = service;
    }

    public static Service getService() {
        return service;
    }

    public static void setStage(Stage stage) {
        ControllerUtils.stage = stage;
    }

    public static void setScene(Scene scene) {
        double height = stage.getHeight();
        double width = stage.getWidth();
        stage.setScene(scene);
        stage.setHeight(height);
        stage.setWidth(width);
    }

    public static void raiseError(String title, String text) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setContentText(text);
        alert.show();
    }
}
