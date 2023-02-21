package application.gui.controller.list;

import application.models.User;
import application.service.exceptions.NotFoundException;
import application.utils.Animations;
import javafx.animation.Animation;
import javafx.fxml.FXML;
import javafx.scene.image.ImageView;
import javafx.scene.text.Text;

import java.io.IOException;

public class MemberCardController extends AbstractCardController<User> {
    private User user;
    @FXML
    public ImageView userPhoto;
    @FXML
    public Text userNameText;
    private Animation hoverAnimation;

    @Override
    public void setEntity(User user) {
        this.user = user;
    }

    @Override
    public void build() {
        userNameText.setText(user.getName());
        userPhoto.setImage(user.getAvatar().getPhoto());
        hoverAnimation = Animations.bounceTransition(userPhoto, 10, 500);
    }

    public void handleElementClicked() throws IOException {
        try {
            interfaceController.showProfileOf(networkService.findFriend(user.getID()));
        } catch (NotFoundException e) {
            throw new RuntimeException(e);
        }
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
