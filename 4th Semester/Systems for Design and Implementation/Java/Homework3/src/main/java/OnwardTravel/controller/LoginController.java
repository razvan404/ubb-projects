package OnwardTravel.controller;

import OnwardTravel.gui.OnwardTravel;
import OnwardTravel.service.Service;
import OnwardTravel.service.exceptions.InvalidDataException;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;

import java.io.IOException;

public class LoginController {
    private final Service service = ControllerUtils.getService();
    @FXML
    protected TextField usernameField;
    @FXML
    protected PasswordField passwordField;

    @FXML
    protected void handleLoginButton() throws IOException {
        try {
            service.tryLogin(usernameField.getText(), passwordField.getText());

            FXMLLoader fxmlLoader = new FXMLLoader(OnwardTravel.class.getResource("main-view.fxml"));
            AnchorPane pane = fxmlLoader.load();
            fxmlLoader.<MainController>getController().build();
            Scene scene = new Scene(pane);
            ControllerUtils.setScene(scene);

        } catch (InvalidDataException ex) {
            ControllerUtils.raiseError("Loggin Error", ex.getMessage());
        }
    }
}
