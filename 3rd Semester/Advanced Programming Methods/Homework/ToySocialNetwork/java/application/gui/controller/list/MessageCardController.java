package application.gui.controller.list;

import application.models.Message;
import application.utils.Animations;
import application.utils.Constants;
import javafx.fxml.FXML;
import javafx.geometry.Pos;
import javafx.scene.control.Tooltip;
import javafx.scene.layout.HBox;
import javafx.scene.text.TextFlow;
import javafx.scene.text.Text;

import java.io.IOException;
import java.time.LocalDate;

public class MessageCardController extends AbstractCardController<Message> {
    private Message message;
    @FXML
    public HBox messageBox;
    @FXML
    public TextFlow messageContainer;
    @FXML
    public Text messageText;

    @Override
    public void setEntity(Message message) {
        this.message = message;
    }

    @Override
    public void build() {
        Tooltip tooltip = new Tooltip(message.getTime().format(Constants.DATE_TIME_FORMATTER));
        if (message.getTime().toLocalDate().equals(LocalDate.now())) {
            tooltip.setText(message.getTime().format(Constants.TIME_FORMATTER));
        }
        Tooltip.install(messageContainer, tooltip);
        messageText.setText(message.getMessage());
        if (!message.getFromUser().equals(networkService.getCurrentUser().getID())) {
            messageBox.setAlignment(Pos.CENTER_LEFT);
        }
        messageBox.setEffect(Animations.getColorAdjust(message.getFromUser()));
    }

    @Override
    public void refresh() throws IOException {}
}
