package application.gui.controller;

import application.gui.SocialNetworkApplication;
import application.gui.controller.list.ContactListController;
import application.gui.controller.list.MessageListController;
import application.gui.controller.windows.InterfaceWindow;
import application.models.Contact;
import application.models.Friend;
import application.models.exceptions.ValidationException;
import application.service.exceptions.AlreadyExistsException;
import application.service.exceptions.NotFoundException;
import application.utils.Animations;
import application.utils.Constants;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Text;

import java.io.IOException;
import java.util.List;

public class MessagesController extends InterfaceWindow {
    private Friend currentFriend;
    @FXML
    public AnchorPane contactsPane;
    @FXML
    public AnchorPane messagesPane;
    @FXML
    public TextField messageField;
    @FXML
    public ScrollPane messagesScrollPane;
    @FXML
    public Button messageButton;
    @FXML
    public ImageView userPhoto;
    @FXML
    public Text userNameText;
    @FXML
    public Text friendsFromText;

    public void setCurrentFriend(Friend friend) {
        this.currentFriend = friend;
    }

    public void build() throws IOException {
        setCurrentInterfaceWindow(this);

        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/list/contact-list.fxml"));
        AnchorPane contactsPane = loader.load();

        List<Contact> contactList = networkService.getContactList();
        loader.<ContactListController>getController().setEntities(contactList);
        loader.<ContactListController>getController().build();

        this.contactsPane.getChildren().setAll(contactsPane);
        AnchorPane.setLeftAnchor(contactsPane, 0d);
        AnchorPane.setRightAnchor(contactsPane, 0d);
        AnchorPane.setTopAnchor(contactsPane, 0d);
        AnchorPane.setBottomAnchor(contactsPane, 0d);

        if (currentFriend == null || !contactList.contains(new Contact(currentFriend,null))) {
            messageField.setDisable(true);
            messageButton.setDisable(true);
            userPhoto.setImage(null);
            userNameText.setText(null);
            friendsFromText.setText(null);
            return;
        }

        messageField.setPromptText("Type a message...");
        messageField.setText(null);

        Animations.bounceTransition(userPhoto).play();
        userPhoto.setImage(currentFriend.getAvatar().getPhoto());
        userNameText.setText(currentFriend.getName());
        friendsFromText.setText("Friends from: " + currentFriend.getFriendsFrom().format(Constants.DATE_TIME_FORMATTER));

        buildMessages();
    }

    public void buildMessages() throws IOException {
        FXMLLoader messagesLoader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/list/message-list.fxml"));
        AnchorPane messagesPane = messagesLoader.load();

        messagesLoader.<MessageListController>getController().setEntities(networkService
                .getMessagesWith(currentFriend.getID()));
        messagesLoader.<MessageListController>getController().build();

        this.messagesPane.getChildren().setAll(messagesPane);
        AnchorPane.setLeftAnchor(messagesPane, 0d);
        AnchorPane.setRightAnchor(messagesPane, 0d);
        AnchorPane.setTopAnchor(messagesPane, 4d);
        AnchorPane.setBottomAnchor(messagesPane, 4d);

        messagesScrollPane.setVvalue(1);
    }

    @FXML
    public void sendMessage() throws IOException {
        try {
            networkService.sendMessageTo(currentFriend.getID(), messageField.getText());
            buildMessages();
        } catch (ValidationException except) {
            messageField.setPromptText(except.getMessage());
            messageField.setText(null);
        } catch (AlreadyExistsException except) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText(except.getMessage());
            alert.show();
        }
    }

    public void handleUserPhotoClicked() throws IOException {
        interfaceController.showProfileOf(currentFriend);
    }

    @Override
    public void refresh() throws IOException {
        if (currentFriend != null) {
            try {
                currentFriend = networkService.findFriend(currentFriend.getID());
            } catch (NotFoundException e) {
                throw new RuntimeException(e);
            }
        }
        build();
    }
}
