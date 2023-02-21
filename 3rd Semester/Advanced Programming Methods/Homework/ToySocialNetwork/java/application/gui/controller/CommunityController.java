package application.gui.controller;

import application.gui.SocialNetworkApplication;
import application.gui.controller.list.MemberListController;
import application.gui.controller.windows.InterfaceWindow;
import application.models.Community;
import application.models.User;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

import java.io.IOException;

public class CommunityController extends InterfaceWindow {
    private User user;
    @FXML
    public Text title;
    @FXML
    public Text errorText;
    @FXML
    public Text usersText;
    @FXML
    public Text friendshipsText;
    @FXML
    public Text ageAverageText;
    @FXML
    public Text socialScoreText;
    @FXML
    public AnchorPane membersPane;
    @FXML
    public VBox errorBox;

    public void setUser(User user) {
        this.user = user;
    }

    public void build() throws IOException {
        setCurrentInterfaceWindow(this);

        if (user.equals(networkService.getCurrentUser())) {
            title.setText("Your community");
        }
        else {
            title.setText(user.getName() + "'s community");
        }

        Community community = networkService.communityService.findCommunityFrom(user.getID());

        if (community == null) {
            errorText.setText("The user need at least 1 friend to become apart of a community.");
            usersText.setText("-");
            ageAverageText.setText("-");
            friendshipsText.setText("-");
            socialScoreText.setText("-");
            return;
        }

        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/list/member-list.fxml"));
        AnchorPane membersPane = loader.load();
        loader.<MemberListController>getController().setEntities(community.getUserList());
        loader.<MemberListController>getController().build();

        this.membersPane.getChildren().setAll(membersPane);
        AnchorPane.setLeftAnchor(membersPane, 0d);
        AnchorPane.setRightAnchor(membersPane, 0d);
        AnchorPane.setTopAnchor(membersPane, 0d);
        AnchorPane.setBottomAnchor(membersPane, 0d);

        errorBox.setVisible(false);
        usersText.setText(Integer.toString(community.getUserList().size()));
        ageAverageText.setText(Double.toString(community.getAgeAverage()));
        friendshipsText.setText(Integer.toString(community.getFriendshipsCount()));
        socialScoreText.setText(Integer.toString(community.getSocialScore()));
    }

    @Override
    public void refresh() throws IOException {
        build();
    }
}
