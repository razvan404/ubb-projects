package application.utils;

import javafx.scene.control.Label;

public class GUIHelper {
    public static Label getBoldLabel(String text) {
        Label label = new Label(text);
        label.setStyle("-fx-font-size: 18px; -fx-font-weight: bold");
        return label;
    }
}
