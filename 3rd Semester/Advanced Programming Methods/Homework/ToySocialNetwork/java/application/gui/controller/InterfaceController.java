package application.gui.controller;

import application.models.Friend;
import application.gui.SocialNetworkApplication;
import application.gui.controller.list.UserListController;
import application.gui.controller.windows.InterfaceWindow;
import application.models.User;
import application.utils.Animations;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;

import java.io.IOException;
import java.util.List;

public class InterfaceController extends InterfaceWindow {
    private boolean isToolBarExtended = true;
    @FXML
    public AnchorPane mainSection;
    @FXML
    public TextField searchField;
    @FXML
    public AnchorPane searchSection;
    @FXML
    public AnchorPane toolBar;

    @FXML
    public void initialize() throws IOException {
        setCurrentWindow(this);

        if (mainSection != null) {
            setInterfaceController(this);
            searchSection.setPrefHeight(0);
            handleMenuButton();
            handleHomeButton();
        }
    }

    public void handleChangeWindow() {
        searchSection.getChildren().clear();
        searchField.setText("");
        if (isToolBarExtended) {
            handleMenuButton();
        }
    }

    public void handleSearchField() throws IOException {
        String searchEntry = searchField.getText();

        if (searchEntry != null && !searchEntry.equals("")) {
            List<Friend> resultList = networkService.findByName(searchEntry);

            FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/list/user-list.fxml"));
            AnchorPane searchedPane = loader.load();

            loader.<UserListController>getController().setEntities(resultList);
            loader.<UserListController>getController().build();

            searchSection.getChildren().setAll(searchedPane);
            AnchorPane.setBottomAnchor(searchedPane, 0d);
            AnchorPane.setLeftAnchor(searchedPane, 0d);
            AnchorPane.setRightAnchor(searchedPane, 0d);
            AnchorPane.setTopAnchor(searchedPane, 0d);
        }
        else {
            searchSection.getChildren().clear();
        }
    }

    public void handleMenuButton() {
        if (!isToolBarExtended) {
            Animations.changeWidthTransition(toolBar, 50, 200).play();
            Animations.changeRightAnchorPaneTransition(mainPane, 45, 195).play();
            isToolBarExtended = true;
        }
        else {
            Animations.changeWidthTransition(toolBar, 200, 50).play();
            Animations.changeRightAnchorPaneTransition(mainPane, 195, 45).play();
            isToolBarExtended = false;
        }
    }

    public void handleHomeButton() throws IOException {
        handleChangeWindow();
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/home.fxml"));
        setMainPaneContent(loader.load());
    }

    public void handleFriendsButton() throws IOException {
        handleChangeWindow();
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/friends.fxml"));
        setMainPaneContent(loader.load());
    }

    public void handleFriendsButton(Friend currentFriend) throws IOException {
        handleChangeWindow();
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/friends.fxml"));
        AnchorPane friendsPane = loader.load();
        loader.<FriendsController>getController().setSelectedFriend(currentFriend);
        setMainPaneContent(friendsPane);
    }

    public void handleCommunityButton() throws IOException {
        handleChangeWindow();
        showCommunityOf(networkService.getCurrentUser());
    }

    public void handleNotificationsButton() throws IOException {
        handleChangeWindow();
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/notifications.fxml"));
        AnchorPane notifications = loader.load();
        setMainPaneContent(notifications);
    }

    public void handleMessagesButton() throws IOException {
        showMessagesWith(null);
    }

    public void handleProfileButton() throws IOException {
        showProfileOf(networkService.getCurrentUser());
    }

    public void handleSettingsButton() throws IOException {
        handleChangeWindow();
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/settings.fxml"));
        AnchorPane notifications = loader.load();
        setMainPaneContent(notifications);
    }

    public void handleSignOutButton() throws IOException {
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/login.fxml"));
        changeScene(loader.load());
    }


    public void showProfileOf(Friend friend) throws IOException {
        handleChangeWindow();
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/profile.fxml"));
        AnchorPane userProfile = loader.load();
        loader.<ProfileController>getController().setUser(friend);
        loader.<ProfileController>getController().build();

        setMainPaneContent(userProfile);
    }

    public void showCommunityOf(User user) throws IOException {
        handleChangeWindow();
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/community.fxml"));
        AnchorPane communityPane = loader.load();
        loader.<CommunityController>getController().setUser(user);
        loader.<CommunityController>getController().build();

        setMainPaneContent(communityPane);
    }

    public void showMessagesWith(Friend friend) throws IOException {
        handleChangeWindow();
        FXMLLoader loader = new FXMLLoader(SocialNetworkApplication.class.getResource("fxml/messages.fxml"));
        AnchorPane messagesPane = loader.load();
        loader.<MessagesController>getController().setCurrentFriend(friend);
        loader.<MessagesController>getController().build();

        setMainPaneContent(messagesPane);
    }

    @Override
    public void refresh() throws IOException {
        currentInterfaceWindow.refresh();
    }
}
