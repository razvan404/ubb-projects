package application.controller;

import application.gui.Main;
import application.models.Client;
import application.models.Hotel;
import application.models.HotelType;
import application.models.SpecialOffer;
import application.service.Service;
import application.utils.GUIHelper;
import application.utils.observer.Observer;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.IOException;
import java.time.LocalDate;
import java.util.List;

public class ClientViewController implements Observer {
    private Service service;
    private Client client;

    @FXML
    public VBox vBox;

    @FXML
    public Label clientNameLabel;
    @FXML
    public Label ageLabel;
    @FXML
    public Label fidelityLabel;
    @FXML
    public Label hobbyLabel;

    private TableView<SpecialOffer> specialView;
    private TableView<Hotel> hotelView;
    public Text reserveError;
    public Button reserveButton;
    public Text notificationText;

    public void setResources(Service service, Client client) {
        this.service = service;
        this.client = client;
        service.addObserver(this);
    }

    public void build() {
        clientNameLabel.setText(client.getName());
        ageLabel.setText("Age: " + client.getAge());
        fidelityLabel.setText("Fidelity grade: " + client.getFidelityGrade());
        hobbyLabel.setText("Hobby: " + client.getHobbies());

        specialView = createSpecialOffersTable(service.getClientSpecialOffers(client));
        hotelView = createHotelsTable(service.getHotels());

        vBox.getChildren().add(GUIHelper.getBoldLabel("Special offers:"));
        vBox.getChildren().add(specialView);
        vBox.getChildren().add(GUIHelper.getBoldLabel("List of hotels:"));
        vBox.getChildren().add(hotelView);

        reserveError = new Text("");
        reserveButton = new Button("Reserve room");
        vBox.getChildren().add(reserveError);
        vBox.getChildren().add(reserveButton);
        reserveButton.setOnAction(event -> handleReserveButton());

        notificationText = new Text("");
        vBox.getChildren().add(notificationText);
    }

    private TableView<SpecialOffer> createSpecialOffersTable(List<SpecialOffer> hotels) {
        TableView<SpecialOffer> specialTable = new TableView<>();

        TableColumn<SpecialOffer, String> hotelNameColumn = new TableColumn<>("Hotel");
        hotelNameColumn.setCellValueFactory(p ->
                new SimpleStringProperty(service.getHotel(p.getValue().getHotelID()).getHotelName()));

        TableColumn<SpecialOffer, LocalDate> startColumn = new TableColumn<>("Start date");
        startColumn.setCellValueFactory(new PropertyValueFactory<>("startDate"));

        TableColumn<SpecialOffer, LocalDate> endColumn = new TableColumn<>("End date");
        endColumn.setCellValueFactory(new PropertyValueFactory<>("endDate"));

        TableColumn<SpecialOffer, Double> priceColumn = new TableColumn<>("Percents");
        priceColumn.setCellValueFactory(new PropertyValueFactory<>("percents"));

        specialTable.getColumns().addAll(hotelNameColumn, startColumn, endColumn, priceColumn);
        specialTable.setItems(FXCollections.observableList(hotels));

        specialTable.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        return specialTable;
    }

    private TableView<Hotel> createHotelsTable(List<Hotel> hotels) {
        TableView<Hotel> hotelsTable = new TableView<>();
        TableColumn<Hotel, String> nameColumn = new TableColumn<>("Name");
        nameColumn.setCellValueFactory(new PropertyValueFactory<>("hotelName"));

        TableColumn<Hotel, Integer> roomsColumn = new TableColumn<>("Rooms");
        roomsColumn.setCellValueFactory(new PropertyValueFactory<>("noRooms"));

        TableColumn<Hotel, Double> priceColumn = new TableColumn<>("Price/Night");
        priceColumn.setCellValueFactory(new PropertyValueFactory<>("perNight"));

        TableColumn<Hotel, HotelType> typeColumn = new TableColumn<>("Type");
        typeColumn.setCellValueFactory(new PropertyValueFactory<>("type"));

        hotelsTable.getColumns().addAll(nameColumn, roomsColumn, priceColumn, typeColumn);
        hotelsTable.setItems(FXCollections.observableList(hotels));

        hotelsTable.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        return hotelsTable;
    }

    public void handleReserveButton() {
        Hotel hotel = hotelView.getSelectionModel().getSelectedItem();

        if (hotel == null) {
            reserveError.setText("Please select a hotel!");
            return;
        }

        Stage stage = new Stage();
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("reservation-view.fxml"));
        AnchorPane reservationPane;
        try {
            reservationPane = fxmlLoader.load();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        fxmlLoader.<ReservationViewController>getController().setResources(service, client, hotel);
        fxmlLoader.<ReservationViewController>getController().build();
        Scene scene = new Scene(reservationPane, 400, 400);
        stage.setTitle("Hotel " + hotel.getHotelName() + " reservation");
        stage.setScene(scene);
        stage.show();

        reserveError.setText("");
    }

    @Override
    public void update(Object... resources) {
        if (resources.length == 2 && resources[0] instanceof Client && resources[1] instanceof Hotel) {
            Client lastClient = (Client) resources[0];
            Hotel hotel = (Hotel) resources[1];
            if (lastClient.getID() != client.getID() && lastClient.getHobbies() == client.getHobbies()) {
                String text = "";
                switch (client.getHobbies()) {
                    case MUSIC -> text = "Un alt gurmand al muzicii si-a inchiriat la hotelul " + hotel.getHotelName();
                    case HIKING -> text = "Un alt pasionat de catarat si-a inchiriat la hotelul " + hotel.getHotelName();
                    case READING -> text = "Iti place sa citesti? Si alt pasionat si-a inchiriat hotelul " + hotel.getHotelName();
                    case WALKING -> text = "Mers incet, mers rapid, alt pasionat de mers si-a inchiriat hotelul " + hotel.getHotelName();
                    case EXTREME_SPORTS -> text = "Iti traiesti viata la extrem? Alt tip de acelasi fel si-a inchiriat hotelul " + hotel.getHotelName();
                }
                notificationText.setText(text);
            }
        }
    }
}
