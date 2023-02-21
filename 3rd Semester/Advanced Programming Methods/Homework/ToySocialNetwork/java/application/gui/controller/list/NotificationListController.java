package application.gui.controller.list;

import application.models.notification.Notification;
import javafx.fxml.FXML;
import javafx.scene.layout.VBox;

public class NotificationListController extends AbstractListController<Notification, NotificationCardController> {
    @FXML
    public VBox vBox;
    @FXML
    public void initialize() {
        setGUIElements("fxml/list/notification-card.fxml", vBox);
    }
}
