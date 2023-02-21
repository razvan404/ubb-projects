package application.gui.controller;

import application.gui.SocialNetworkApplication;
import application.gui.controller.windows.ApplicationWindow;
import application.service.exceptions.NotFoundException;
import application.utils.Animations;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

import java.io.IOException;

public class LoginController extends ApplicationWindow {
    @FXML
    public TextField mailField;
    @FXML
    public PasswordField passwordField;
    @FXML
    public Text errorText;
    @FXML
    public VBox frameBox;

    @FXML
    public void initialize() {
        setCurrentWindow(this);

        mailField.setText(null);
        passwordField.setText(null);
        errorText.setText(null);

        Animations.changeWidthTransition(frameBox, 380, 300).play();
        Animations.changeHeightTransition(frameBox, 550, 450).play();

        mailField.focusedProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue) {
                // Move the prompt text up when the TextField is focused
                mailField.getChildrenUnmodifiable().stream()
                        .filter(node -> node instanceof Text)
                        .findFirst()
                        .ifPresent(node -> node.setTranslateY(-20));
            } else {
                // Move the prompt text back down when the TextField is no longer focused
                mailField.getChildrenUnmodifiable().stream()
                        .filter(node -> node instanceof Text)
                        .findFirst()
                        .ifPresent(node -> node.setTranslateY(0));
            }
        });
    }

    public void handleLoginButton() throws IOException {
        try {
            networkService.login(mailField.getText(), passwordField.getText());
            FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/interface.fxml"));
            changeScene(loader.load());
        } catch (IllegalArgumentException | NotFoundException e) {
            errorText.setText(e.getMessage());
        }
    }
    public void handleRegisterHyperlink() throws IOException {
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/register.fxml"));
        changeScene(loader.load());
    }

    @Override
    public void refresh() throws IOException {
        initialize();
    }
}
