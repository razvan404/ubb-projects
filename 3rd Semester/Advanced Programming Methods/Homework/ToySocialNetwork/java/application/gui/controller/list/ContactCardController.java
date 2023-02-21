package application.gui.controller.list;

import application.models.Contact;
import application.utils.Animations;
import javafx.animation.Animation;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.text.Text;

import java.io.IOException;

public class ContactCardController extends AbstractCardController<Contact> {
    private Contact contact;
    @FXML
    public ImageView userPhoto;
    @FXML
    public Text userNameText;
    @FXML
    public Label messageLabel;
    private Animation hoverAnimation;

    @Override
    public void setEntity(Contact contact) {
        this.contact = contact;
    }

    @Override
    public void build() {
        hoverAnimation = Animations.bounceTransition(userPhoto, 10, 500);

        userPhoto.setImage(contact.getAvatar().getPhoto());
        userNameText.setText(contact.getName());
        if (contact.getLastMessage() != null) {
            if (contact.getLastMessage().getFromUser().equals(networkService.getCurrentUser().getID())) {
                messageLabel.setText("You: " + contact.getLastMessage().getMessage());
            }
            else {
                messageLabel.setText(contact.getName() + ": " + contact.getLastMessage().getMessage());
            }
        }
        else {
            messageLabel.setText(null);
        }
    }

    public void handleElementClicked() throws IOException {
        interfaceController.showMessagesWith(contact);
    }

    public void handleElementEntered() {
        hoverAnimation.play();
    }

    public void handleElementExited() {
        hoverAnimation.stop();
        userPhoto.setRotate(0);
    }

    @Override
    public void refresh() throws IOException {}
}
