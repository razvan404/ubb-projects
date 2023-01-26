package application.gui.controller.list;

import application.models.Friend;
import application.utils.Animations;
import application.utils.Constants;
import javafx.animation.Animation;
import javafx.fxml.FXML;
import javafx.scene.image.ImageView;
import javafx.scene.text.Text;

import java.io.IOException;

public class UserCardController extends AbstractCardController<Friend> {
    private Friend friend;
    @FXML
    public ImageView userPhoto;
    @FXML
    public Text userNameText;
    @FXML
    public Text friendsFromText;
    @FXML
    public Text inCommonText;
    private Animation hoverAnimation;

    @Override
    public void setEntity(Friend friend) {
        this.friend = friend;
    }

    @Override
    public void build() {
        userNameText.setText(friend.getName());
        userPhoto.setImage(friend.getAvatar().getPhoto());
        if (friend.getFriendsFrom() != null) {
            friendsFromText.setText("Friends from: " + friend.getFriendsFrom().format(Constants.DATE_FORMATTER));
        }
        else {
            friendsFromText.setText("");
        }
        if (friend.getCommonFriends() == 0) {
            inCommonText.setText("");
        }
        else {
            inCommonText.setText("Common friends: " + friend.getCommonFriends());
        }
        hoverAnimation = Animations.bounceTransition(userPhoto, 10, 500);
    }

    public void handleElementClicked() throws IOException {
        interfaceController.showProfileOf(friend);
    }

    public void handleElementEntered() {
        hoverAnimation.play();
    }

    public void handleElementExited() {
        hoverAnimation.stop();
        userPhoto.setRotate(0);
    }

    @Override
    public void refresh() throws IOException {
        build();
    }
}
