package application.gui.controller;

import application.gui.SocialNetworkApplication;
import application.gui.controller.list.NotificationListController;
import application.gui.controller.windows.InterfaceWindow;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;

import java.io.IOException;

public class NotificationsController extends InterfaceWindow {
    @FXML
    public AnchorPane notificationsPane;

    @FXML
    public void initialize() throws IOException {
        setCurrentInterfaceWindow(this);

        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/list/notification-list.fxml"));
        AnchorPane notificationsPane = loader.load();

        loader.<NotificationListController>getController().setEntities(networkService.getNotificationList());
        loader.<NotificationListController>getController().build();

        this.notificationsPane.getChildren().setAll(notificationsPane);
        AnchorPane.setLeftAnchor(notificationsPane, 2d);
        AnchorPane.setRightAnchor(notificationsPane, 0d);
        AnchorPane.setTopAnchor(notificationsPane, 2d);
        AnchorPane.setBottomAnchor(notificationsPane, 2d);
    }

    @Override
    public void refresh() throws IOException {
        initialize();
    }
}
