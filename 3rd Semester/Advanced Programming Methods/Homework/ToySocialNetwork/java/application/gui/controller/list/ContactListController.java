package application.gui.controller.list;

import application.models.Contact;
import javafx.fxml.FXML;
import javafx.scene.layout.VBox;

public class ContactListController extends AbstractListController<Contact, ContactCardController> {
    @FXML
    public VBox vBox;
    @FXML
    public void initialize() {
        setGUIElements("fxml/list/contact-card.fxml", vBox);
    }
}
