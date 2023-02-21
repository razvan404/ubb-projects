package application.gui;

import application.gui.controller.windows.ApplicationWindow;

import application.repository.database.*;
import application.service.*;
import application.utils.database.DataBase;
import application.utils.database.NetworkDataBase;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;

import java.io.IOException;

public class SocialNetworkApplication extends Application {
    private final DataBase networkDB = NetworkDataBase.getInstance();

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws IOException {
        ApplicationWindow.setApplicationStage(stage);
        ApplicationWindow.setNetworkService(new NetworkService(
                new UserService(new UserRepositoryDB(networkDB)),
                new FriendshipService(new FriendshipRepositoryDB(networkDB)),
                new CommunityService(new CommunityRepositoryDB(networkDB)),
                new NotificationService(new NotificationRepositoryDB(networkDB)),
                new MessageService(new MessageRepositoryDB(networkDB))));

        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/window.fxml"));
        ApplicationWindow.setScene(loader.load());

        stage.show();
    }
}
