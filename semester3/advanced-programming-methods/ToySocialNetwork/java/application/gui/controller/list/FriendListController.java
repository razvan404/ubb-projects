package application.gui.controller.list;

import application.models.Friend;
import javafx.fxml.FXML;
import javafx.scene.layout.FlowPane;

public class FriendListController extends AbstractListController<Friend, FriendCardController> {
    @FXML
    public FlowPane flowPane;
    @FXML
    public void initialize() {
        setGUIElements("fxml/list/friend-card.fxml", flowPane);
    }
}