package client.controller;

import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.stage.Stage;
import models.Reservation;
import models.User;
import service.UserService;
import service.observer.UserObserver;

public class ControllerUtils {
    private UserService service = null;
    private Stage stage;
    private User currentUser = null;
    private MainViewController mainController;
    private ObserverComponent instance;

    public ObserverComponent getObserverComponent() {
        if (instance == null) {
            instance = new ObserverComponent();
        }
        return instance;
    }


    public void setMainController(MainViewController controller) {
        mainController = controller;
    }
    public void setService(UserService service) {
        this.service = service;
    }

    public UserService getService() {
        return service;
    }

    public void setStage(Stage stage) {
        this.stage = stage;
    }

    public void setScene(Scene scene) {
        double height = stage.getHeight();
        double width = stage.getWidth();
        stage.setScene(scene);
        stage.setHeight(height);
        stage.setWidth(width);
    }

    public void setCurrentUser(User user) {
        currentUser = user;
    }

    public User getCurrentUser() {
        return currentUser;
    }

    public void raiseError(String title, String text) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setContentText(text);
        alert.show();
    }

    private class ObserverComponent implements UserObserver {
        @Override
        public void handleReservationCreated(Reservation reservation) {
            mainController.loadReservations();
            mainController.loadRides();
        }
    }
}
