package client;

import client.controller.ControllerUtils;
import client.controller.LoginViewController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import network.protocol.UserRpcProxyService;
import service.UserService;

import java.io.IOException;
import java.util.Properties;

public class StartRpcClientFX extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Properties clientProps = getProperties();

        String serverIP = clientProps.getProperty("server.host");
        int serverPort = Integer.parseInt(clientProps.getProperty("server.port"));

        UserService service = new UserRpcProxyService(serverIP, serverPort);

        ControllerUtils utils = new ControllerUtils();
        utils.setService(service);
        utils.setStage(stage);

        FXMLLoader fxmlLoader = new FXMLLoader(StartRpcClientFX.class.getResource("login-view.fxml"));
        AnchorPane anchorPane = fxmlLoader.load();
        fxmlLoader.<LoginViewController>getController().build(utils);
        Scene scene = new Scene(anchorPane, 800, 600);
        stage.setTitle("Onward Travel");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }

    public static Properties getProperties() {
        Properties serverProps = new Properties();
        try {
            serverProps.load(StartRpcClientFX.class.getResourceAsStream("/client.properties"));
            System.out.println("Client properties set.");
            serverProps.list(System.out);
        } catch (IOException ex) {
            System.err.println("Cannot find server.properties " + ex);
        }
        return serverProps;
    }
}
