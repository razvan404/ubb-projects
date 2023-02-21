package application.gui.controller;

import application.models.Friend;
import application.models.notification.Notification;
import application.gui.SocialNetworkApplication;
import application.gui.controller.list.UserListController;
import application.service.exceptions.NotFoundException;
import application.utils.Animations;
import application.utils.Constants;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;

import java.io.IOException;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.List;

public class ProfileController extends InterfaceController {
    private Friend friend;

    /**
     * The <b>button flag</b> should be:<br>
     *  <i>0 - when the profile is owned by the current user<br>
     *  1 - when the profile is owned by a friend of the current user<br>
     *  2 - when the profile is owned by a person who don't have anything to do with the user<br>
     *  3 - when the profile is owned by a person who the current user send a friend request to<br>
     *  4 - when the profile is owned by a person who the current user received a friend request from<br></i>
     */
    private int buttonFlag;
    /**
     * Should be the friend request between the current user and the user that owns the profile, it's null otherwise
     */
    private Notification friendRequest;
    @FXML
    public Text userNameText;
    @FXML
    public Text friendsFromText;
    @FXML
    public Text memberSinceText;
    @FXML
    public Text birthDateText;
    @FXML
    public Text biographyTitle;
    @FXML
    public Text biographyText;
    @FXML
    public Text friendsText;
    @FXML
    public Text inCommonText;
    @FXML
    public Button profileButton;
    @FXML
    public AnchorPane friendsPane;

    @FXML
    public AnchorPane backgroundPane;

    @FXML
    public ImageView profileImage;

    @FXML
    public HBox buttonsBox;
    @FXML
    public Label buttonLabel;

    @FXML
    public ImageView buttonImage;
    @FXML
    public Button communityButton;
    @FXML
    public Button messageButton;

    @FXML
    public void initialize() {
        setCurrentInterfaceWindow(this);
    }

    public void setUser(Friend friend) {
        this.friend = friend;
    }

    public void build() throws IOException {
        Animations.bounceTransition(profileImage).play();

        backgroundPane.setEffect(Animations.getColorAdjust(friend.getID()));

        profileImage.setImage(friend.getAvatar().getPhoto());

        userNameText.setText(friend.getName());
        if (friend.getFriendsFrom() != null) {
            friendsFromText.setText("Friends from: " + friend.getFriendsFrom().format(Constants.DATE_TIME_FORMATTER));
        }
        else {
            friendsFromText.setText("");
        }
        memberSinceText.setText(friend.getRegisterDate().format(Constants.DATE_FORMATTER) + " (" +
                ChronoUnit.DAYS.between(friend.getRegisterDate(), LocalDate.now()) + " days)");
        birthDateText.setText(friend.getBirthDate().format(Constants.DATE_FORMATTER) + " (" +
                friend.getAge() + " years)");

        if (friend.getBiography() != null) {
            biographyText.setText(friend.getBiography());
        }
        else {
            biographyText.setText("");
            biographyTitle.setText("");
        }


        if (friend.getID().equals(networkService.getCurrentUser().getID()) || friend.getCommonFriends() == 0) {
            inCommonText.setText("");
        }
        else {
            inCommonText.setText("(" + friend.getCommonFriends() + " in common)");
        }

        if (networkService.getCurrentUser().getID().equals(friend.getID())) {
            buttonFlag = 0;
            profileButton.getStyleClass().setAll("account-settings-button");
            buttonLabel.setText("Account settings");
            buttonImage.setImage(new Image("/application/gui/media/icons/profile-account-settings.png"));
            buttonsBox.getChildren().remove(communityButton);
            buttonsBox.getChildren().remove(messageButton);
        }
        else if (networkService.findFriendsOf(networkService.getCurrentUser().getID())
                .stream().map(Friend::getID).toList().contains(friend.getID())) {
            buttonFlag = 1;
            profileButton.getStyleClass().setAll("friend-button");
            buttonLabel.setText("Remove friend");
            buttonImage.setImage(new Image("/application/gui/media/icons/profile-remove-friend.png"));
        }
        else {
            profileButton.getStyleClass().setAll("friend-button");
            buttonImage.setImage(new Image("/application/gui/media/icons/profile-add-friend.png"));
            friendRequest = networkService.getFriendRequest(friend.getID());
            buttonsBox.getChildren().remove(messageButton);
            if (friendRequest == null) {
                buttonFlag = 2;
                buttonLabel.setText("Friend request");
            }
            else if (networkService.getCurrentUser().getID().equals(friendRequest.getFromUser())) {
                buttonFlag = 3;
                buttonLabel.setText("Cancel request");
            }
            else {
                buttonFlag = 4;
                buttonLabel.setText("Accept request");
            }
        }

        handleFriends();
    }

    @FXML
    public void handleFriends() throws IOException {
        List<Friend> resultList = networkService.findFriendsOf(friend.getID());

        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/list/user-list.fxml"));
        AnchorPane friendsPane = loader.load();

        loader.<UserListController>getController().setEntities(resultList);
        loader.<UserListController>getController().build();

        this.friendsPane.getChildren().setAll(friendsPane);
        AnchorPane.setLeftAnchor(friendsPane, 0d);
        AnchorPane.setRightAnchor(friendsPane, 0d);
        AnchorPane.setTopAnchor(friendsPane, 0d);
        AnchorPane.setBottomAnchor(friendsPane, 0d);
    }

    @FXML
    public void handleCommonFriends() throws IOException {
        List<Friend> resultList = networkService.findCommonFriends(friend.getID());

        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/list/user-list.fxml"));
        AnchorPane friendsPane = loader.load();

        loader.<UserListController>getController().setEntities(resultList);
        loader.<UserListController>getController().build();

        this.friendsPane.getChildren().setAll(friendsPane);
        AnchorPane.setLeftAnchor(friendsPane, 0d);
        AnchorPane.setRightAnchor(friendsPane, 0d);
        AnchorPane.setTopAnchor(friendsPane, 0d);
        AnchorPane.setBottomAnchor(friendsPane, 0d);
    }

    @FXML
    public void handleButton() throws IOException {
        switch (buttonFlag) {
            case 0 -> interfaceController.handleSettingsButton();
            case 1 -> {
                try {
                    networkService.removeFriend(friend.getID());
                    interfaceController.showProfileOf(friend);
                } catch (Exception e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setContentText(e.getMessage());
                    alert.show();
                }
            }
            case 2 -> {
                try {
                    networkService.sendFriendRequest(friend.getID());
                    interfaceController.showProfileOf(friend);
                } catch (Exception e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setContentText(e.getMessage());
                    alert.show();
                }
            }
            case 3 -> {
                networkService.notificationService.delete(friendRequest.getID());
                interfaceController.showProfileOf(friend);
            }
            case 4 -> {
                try {
                    networkService.acceptFriendRequest(friendRequest);
                    interfaceController.showProfileOf(friend);
                } catch (Exception e) {
                    Alert alert = new Alert(Alert.AlertType.ERROR);
                    alert.setContentText(e.getMessage());
                    alert.show();
                }
            }
        }
    }

    @FXML
    public void handleFriendCommunityButton() throws IOException {
        interfaceController.showCommunityOf(friend);
    }

    @FXML
    public void handleMessageButton() throws IOException {
        interfaceController.showMessagesWith(friend);
    }

    @Override
    public void refresh() throws IOException {
        try {
            friend = networkService.findFriend(friend.getID());
        } catch (NotFoundException e) {
            throw new RuntimeException(e);
        }
        build();
    }
}
