package application.gui.controller;

import application.gui.SocialNetworkApplication;
import application.gui.controller.list.FriendListController;
import application.gui.controller.windows.InterfaceWindow;
import application.models.Friend;
import application.utils.Animations;
import application.utils.Constants;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Alert;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Text;

import java.io.IOException;

public class FriendsController extends InterfaceWindow {
    private Friend selectedFriend;
    @FXML
    public AnchorPane friendsPane;
    @FXML
    public Text friendNameText;
    @FXML
    public Text friendsFromAuxText;
    @FXML
    public Text friendsFromText;
    @FXML
    public ImageView friendPhoto;
    @FXML
    public Text errorText;

    @FXML
    public void initialize() throws IOException {
        setCurrentInterfaceWindow(this);

        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/list/friend-list.fxml"));
        AnchorPane friendsPane = loader.load();

        loader.<FriendListController>getController().setEntities(networkService.findFriendsOf(networkService.getCurrentUser().getID()));
        loader.<FriendListController>getController().build();

        this.friendsPane.getChildren().setAll(friendsPane);
        AnchorPane.setLeftAnchor(friendsPane, 0d);
        AnchorPane.setRightAnchor(friendsPane, 0d);
        AnchorPane.setTopAnchor(friendsPane, 0d);
        AnchorPane.setBottomAnchor(friendsPane, 0d);

        this.selectedFriend = null;
        friendNameText.setText("none");
        friendsFromAuxText.setText(null);
        friendsFromText.setText(null);
        errorText.setText(null);
        friendPhoto.setImage(null);
    }

    public void setSelectedFriend(Friend friend) {
        this.selectedFriend = friend;
        friendNameText.setText(friend.getName());
        friendsFromAuxText.setText("Friends from:");
        friendsFromText.setText(friend.getFriendsFrom().format(Constants.DATE_TIME_FORMATTER));
        friendPhoto.setImage(friend.getAvatar().getPhoto());
        errorText.setText(null);
        Animations.bounceTransition(friendPhoto).play();
    }

    @FXML
    public void handleProfileButton() throws IOException {
        if (selectedFriend == null) {
            errorText.setText("Please select a friend!");
            return;
        }
        interfaceController.showProfileOf(selectedFriend);
    }

    @FXML
    public void handleMessageButton() throws IOException {
        if (selectedFriend == null) {
            errorText.setText("Please select a friend!");
            return;
        }
        interfaceController.showMessagesWith(selectedFriend);
    }

    @FXML
    public void handleRemoveButton() {
        if (selectedFriend == null) {
            errorText.setText("Please select a friend!");
            return;
        }
        try {
            networkService.removeFriend(selectedFriend.getID());
            interfaceController.handleFriendsButton();
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText(e.getMessage());
            alert.show();
        }
    }

    @Override
    public void refresh() throws IOException {
        initialize();
    }
}
