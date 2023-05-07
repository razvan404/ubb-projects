package client.controller;

import client.StartRpcClientFX;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import models.User;
import service.UserService;
import service.exceptions.InvalidDataException;

import java.io.IOException;

public class LoginViewController {
    private UserService service;
    private ControllerUtils utils;
    @FXML
    protected TextField usernameField;
    @FXML
    protected PasswordField passwordField;

    public void build(ControllerUtils utils) {
        this.utils = utils;
        service = utils.getService();
    }

    @FXML
    protected void handleLoginButton() {
        Platform.runLater(() -> {
            try {
                User user = service.tryLogin(new User(usernameField.getText(), passwordField.getText()),
                        utils.getObserverComponent());
                utils.setCurrentUser(user);

                FXMLLoader fxmlLoader = new FXMLLoader(StartRpcClientFX.class.getResource("main-view.fxml"));
                AnchorPane pane = fxmlLoader.load();
                fxmlLoader.<MainViewController>getController().build(utils);
                Scene scene = new Scene(pane);
                utils.setScene(scene);

            } catch (InvalidDataException ex) {
                utils.raiseError("Login Error", ex.getMessage());
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        });
    }
}
