package application.gui.controller.list;

import application.models.Message;
import javafx.fxml.FXML;
import javafx.scene.layout.VBox;

public class MessageListController extends AbstractListController<Message, MessageCardController> {
    @FXML
    public VBox vBox;
    @FXML
    public void initialize() {
        setGUIElements("fxml/list/message-card.fxml", vBox);
    }
}
