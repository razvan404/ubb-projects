package application.gui.controller;

import application.gui.controller.windows.InterfaceWindow;
import application.utils.Animations;
import javafx.fxml.FXML;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class HomeController extends InterfaceWindow {
    @FXML
    public Text usersCount;
    @FXML
    public Text friendshipsCount;
    @FXML
    public AnchorPane usersPane;
    @FXML
    public AnchorPane friendshipsPane;
    @FXML
    public AnchorPane chatterPane;

    @FXML
    public VBox backgroundBox;

    @FXML
    public void initialize() {
        setCurrentInterfaceWindow(this);
        usersCount.setText(String.valueOf(networkService.userService.size()));
        friendshipsCount.setText(String.valueOf(networkService.friendshipService.size()));
        Animations.hueTransition(backgroundBox, 5000).play();
    }

    @Override
    public void refresh()  {
        initialize();
    }
}
