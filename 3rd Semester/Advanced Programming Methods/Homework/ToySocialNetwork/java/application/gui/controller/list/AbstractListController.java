package application.gui.controller.list;

import application.gui.SocialNetworkApplication;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;

import java.io.IOException;
import java.util.List;

public abstract class AbstractListController<E, C extends AbstractCardController<E>> {
    private List<E> entities;
    private String location;
    public Pane container;

    public void setGUIElements(String location, Pane container) {
        this.location = location;
        this.container = container;

    }
    public void setEntities(List<E> entities) {
        this.entities = entities;
    }

    public void build() throws IOException {
        container.getChildren().clear();

        for (E entity : entities) {
            FXMLLoader fxmlLoader = new FXMLLoader(SocialNetworkApplication.class.getResource(location));
            AnchorPane entityPane = fxmlLoader.load();
            fxmlLoader.<C>getController().setEntity(entity);
            fxmlLoader.<C>getController().build();
            container.getChildren().add(entityPane);
        }
    }
}
