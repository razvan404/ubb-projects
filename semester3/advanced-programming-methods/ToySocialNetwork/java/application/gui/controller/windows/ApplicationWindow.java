package application.gui.controller.windows;

import application.gui.controller.WindowController;
import application.service.NetworkService;
import application.utils.Constants;
import application.utils.ResizeHelper;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

import java.io.IOException;

public abstract class ApplicationWindow {
    protected static NetworkService networkService;
    private static WindowController windowController;
    protected static ApplicationWindow currentWindow;
    public static Stage applicationStage;

    public static void setCurrentWindow(ApplicationWindow applicationWindow) {
        currentWindow = applicationWindow;
    }

    public static void setNetworkService(NetworkService networkService) {
        ApplicationWindow.networkService = networkService;
    }

    public static void setWindowController(WindowController windowController) {
        ApplicationWindow.windowController = windowController;
    }

    public static void setApplicationStage(Stage applicationStage) {
        ApplicationWindow.applicationStage = applicationStage;
        ApplicationWindow.applicationStage.initStyle(StageStyle.TRANSPARENT);
        ApplicationWindow.applicationStage.getIcons().setAll(Constants.APP_ICON);
        ApplicationWindow.applicationStage.setTitle("Chatter");
        ApplicationWindow.applicationStage.setMinWidth(800);
        ApplicationWindow.applicationStage.setWidth(800);
        ApplicationWindow.applicationStage.setMinHeight(600);
        ApplicationWindow.applicationStage.setHeight(600);
    }

    public static void changeScene(Node content) {
        ApplicationWindow.windowController.windowPane.getChildren().setAll(content);
        AnchorPane.setBottomAnchor(content, 0d);
        AnchorPane.setLeftAnchor(content, 0d);
        AnchorPane.setRightAnchor(content, 0d);
        AnchorPane.setTopAnchor(content, 0d);
    }

    public static void setScene(Parent root) {
        Scene scene = new Scene(root);
        scene.setFill(Color.TRANSPARENT);
        applicationStage.setScene(scene);
        ResizeHelper.addResizeListener(applicationStage);
        root.requestFocus();
    }

    public static void refreshCurrentWindow() throws IOException {
        currentWindow.refresh();
    }

    public abstract void refresh() throws IOException;
}
