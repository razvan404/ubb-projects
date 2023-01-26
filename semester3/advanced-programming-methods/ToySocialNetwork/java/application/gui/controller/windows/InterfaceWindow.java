package application.gui.controller.windows;

import application.gui.controller.InterfaceController;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.layout.AnchorPane;

public abstract class InterfaceWindow extends ApplicationWindow {
    @FXML
    protected static AnchorPane mainPane;
    protected static InterfaceController interfaceController;
    protected static InterfaceWindow currentInterfaceWindow;

    public static void setInterfaceController(InterfaceController interfaceController) {
        InterfaceWindow.interfaceController = interfaceController;
        InterfaceWindow.mainPane = interfaceController.mainSection;
    }

    public static void setCurrentInterfaceWindow(InterfaceWindow interfaceWindow) {
        currentInterfaceWindow = interfaceWindow;
    }

    public static void setMainPaneContent(Node content) {
        mainPane.getChildren().setAll(content);
        AnchorPane.setBottomAnchor(content, 0d);
        AnchorPane.setLeftAnchor(content, 0d);
        AnchorPane.setRightAnchor(content, 0d);
        AnchorPane.setTopAnchor(content, 0d);
        content.requestFocus();
    }
}
