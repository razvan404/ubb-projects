package application.controller;

import application.gui.Main;
import application.models.Hotel;
import application.models.HotelType;
import application.models.Location;
import application.repository.LocationRepository;
import application.service.Service;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

@SuppressWarnings("unchecked")
public class MainViewController {
    private Service service;
    @FXML
    public VBox vBox;

    public TableView<Hotel> tableView;

    public void setService(Service service) {
        this.service = service;
    }

    public void build() {
        ComboBox<Location> locationsComboBox = new ComboBox<>(FXCollections
                .observableList(service.getLocations()));

        tableView = createHotelsTable(service.getHotels());
        vBox.getChildren().add(tableView);

        locationsComboBox.setPromptText("Select a location");
        locationsComboBox.setOnAction(event -> tableView.setItems(FXCollections
                .observableList(service.getHotelsFrom(locationsComboBox.getValue()))));
        vBox.getChildren().add(locationsComboBox);

        tableView.getSelectionModel().selectedItemProperty().addListener(event -> handleHotelSelection());
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

    private void handleHotelSelection() {
        Hotel hotel = tableView.getSelectionModel().getSelectedItem();

        if (hotel != null) {
            Stage stage = new Stage();
            FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("special-view.fxml"));
            AnchorPane specialPane;
            try {
                specialPane = fxmlLoader.load();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            fxmlLoader.<SpecialViewController>getController().setResources(service, hotel);
            fxmlLoader.<SpecialViewController>getController().build();
            Scene scene = new Scene(specialPane, 400, 600);
            stage.setTitle("Hotel " + hotel.getHotelName() + " special offers");
            stage.setScene(scene);
            stage.show();
        }
    }
}
