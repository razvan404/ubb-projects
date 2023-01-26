package application.gui.controller.list;

import application.models.User;
import javafx.fxml.FXML;
import javafx.scene.layout.FlowPane;

public class MemberListController extends AbstractListController<User, MemberCardController> {
    @FXML
    public FlowPane flowPane;
    @FXML
    public void initialize() {
        setGUIElements("fxml/list/member-card.fxml", flowPane);
    }
}