package application.gui.controller;

import application.gui.SocialNetworkApplication;
import application.gui.controller.windows.ApplicationWindow;
import application.utils.Animations;
import application.utils.ResizeHelper;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.AnchorPane;

import java.io.IOException;

public class WindowController {
    boolean maximized = false;
    @FXML
    public AnchorPane barPane;
    @FXML
    public AnchorPane windowPane;
    @FXML
    public Button refreshButton;

    @FXML
    public void initialize() throws IOException {
        ApplicationWindow.setWindowController(this);

        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/login.fxml"));
        ApplicationWindow.changeScene(loader.load());
        barPane.setOnMouseClicked(event -> {
            if(event.getButton().equals(MouseButton.PRIMARY) && event.getClickCount() == 2) {
                handleMaximizeButton();
            }
        });
    }

    @FXML
    public void handleCloseButton() {
        ApplicationWindow.applicationStage.close();
    }

    @FXML
    public void handleMaximizeButton() {
        maximized = !maximized;
        ResizeHelper.setMaximized(ApplicationWindow.applicationStage, maximized);
    }

    @FXML
    public void handleMinimizeButton() {
        ApplicationWindow.applicationStage.setIconified(true);
    }

    @FXML
    public void handleRefreshButton() throws IOException {
        Animations.rotateTransition(refreshButton).play();
        ApplicationWindow.refreshCurrentWindow();
    }
}
