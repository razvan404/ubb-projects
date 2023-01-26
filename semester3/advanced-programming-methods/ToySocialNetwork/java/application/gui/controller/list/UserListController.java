package application.gui.controller.list;

import application.models.Friend;
import javafx.fxml.FXML;
import javafx.scene.layout.VBox;

public class UserListController extends AbstractListController<Friend, UserCardController> {
    @FXML
    public VBox vBox;
    @FXML
    public void initialize() {
        setGUIElements("fxml/list/user-card.fxml", vBox);
    }
}
