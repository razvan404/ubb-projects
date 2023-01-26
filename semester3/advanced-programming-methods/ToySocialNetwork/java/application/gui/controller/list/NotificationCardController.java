package application.gui.controller.list;

import application.models.exceptions.ValidationException;
import application.models.notification.Notification;
import application.service.exceptions.AlreadyExistsException;
import application.utils.Animations;
import application.utils.Constants;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;

import java.io.IOException;

public class NotificationCardController extends AbstractCardController<Notification> {
    private Notification notification;

    @FXML
    public ImageView removeNotificationImage;
    @FXML
    public ImageView notificationImage;
    @FXML
    public Text titleText;
    @FXML
    public Text messageText;
    @FXML
    public TextFlow messageTextFlow;
    @FXML
    public Text dateText;
    @FXML
    public Button acceptButton;
    @FXML
    public Button rejectButton;

    @Override
    public void setEntity(Notification notification) {
        this.notification = notification;
    }

    @Override
    public void build() {
        removeNotificationImage.setVisible(false);
        switch (notification.getType()) {
            case INFORMATIVE -> notificationImage.setImage(new Image("/application/gui/media/icons/notification-info.png"));
            case FRIEND_REQUEST -> {
                messageTextFlow.setPrefWidth(240);
                notificationImage.setImage(new Image("/application/gui/media/icons/notification-friend-request.png"));
                acceptButton.setVisible(true);
                rejectButton.setVisible(true);
            }
            case FRIEND_REQUEST_ACCEPTED -> notificationImage.setImage(new Image("/application/gui/media/icons/notification-accepted.png"));
            case FRIEND_REQUEST_REJECTED -> notificationImage.setImage(new Image("/application/gui/media/icons/notification-rejected.png"));
            case FRIEND_REMOVED -> notificationImage.setImage(new Image("/application/gui/media/icons/notification-removed.png"));
        }
        Animations.bounceTransition(removeNotificationImage).play();

        titleText.setText(notification.getTitle());
        messageText.setText(notification.getMessage());
        dateText.setText(notification.getDate().format(Constants.DATE_TIME_FORMATTER));
    }

    public void handleImageEntered() {
        if (!rejectButton.isVisible()) {
            removeNotificationImage.setVisible(true);
        }
    }

    public void handleImageExited() {
        removeNotificationImage.setVisible(false);
    }

    public void handleAcceptButton() throws IOException {
        try {
            networkService.acceptFriendRequest(notification);
            interfaceController.handleNotificationsButton();
        } catch (ValidationException | AlreadyExistsException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText(e.getMessage());
            alert.show();
        }
    }

    public void handleImageClicked() throws IOException {
        if (!rejectButton.isVisible()) {
            networkService.notificationService.delete(notification.getID());
            interfaceController.handleNotificationsButton();
        }
    }

    public void handleRejectButton() throws IOException {
        try {
            networkService.rejectFriendRequest(notification);
            interfaceController.handleNotificationsButton();
        } catch (ValidationException | AlreadyExistsException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText(e.getMessage());
            alert.show();
        }
    }

    @Override
    public void refresh() throws IOException {
        build();
    }
}
