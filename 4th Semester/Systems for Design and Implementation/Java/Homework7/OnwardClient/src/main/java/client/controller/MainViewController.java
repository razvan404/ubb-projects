package client.controller;

import client.StartRpcClientFX;
import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Text;
import models.ClientSeat;
import models.Ride;
import service.UserService;
import service.exceptions.InvalidDataException;
import utils.Constants;

import java.io.IOException;

public class MainViewController {
    private ControllerUtils utils;
    private UserService service;
    private Ride selectedRide = null;
    @FXML
    protected Text welcomeText;
    @FXML
    protected TableView<Ride> ridesTable;
    @FXML
    protected TableView<ClientSeat> reservationsTable;
    @FXML
    protected TextField destinationField;
    @FXML
    protected DatePicker departurePicker;
    @FXML
    protected Text destinationText;
    @FXML
    protected Text departureText;
    @FXML
    protected TextField nameField;
    @FXML
    protected TextField phoneField;
    @FXML
    protected TextField seatsCountField;

    public void build(ControllerUtils utils) {
        this.utils = utils;
        this.service = utils.getService();
        utils.setMainController(this);

        welcomeText.setText("Welcome, " + utils.getCurrentUser().getUsername() + "!");
        createRidesTable();
        createReservationsTable();
    }

    @FXML
    public void handleLogOutButton() {
        Platform.runLater(() -> {
            try {
                service.logout(utils.getObserverComponent());
                FXMLLoader fxmlLoader = new FXMLLoader(StartRpcClientFX.class.getResource("login-view.fxml"));
                AnchorPane pane = fxmlLoader.load();
                fxmlLoader.<LoginViewController>getController().build(utils);
                Scene scene = new Scene(pane);
                utils.setScene(scene);
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        });
    }

    public void createRidesTable() {
        Platform.runLater(() -> {
            TableColumn<Ride, String> destinationColumn = new TableColumn<>("Destination");
            destinationColumn.setCellValueFactory(new PropertyValueFactory<>("destination"));

            TableColumn<Ride, String> departureColumn = new TableColumn<>("Departure");
            departureColumn.setCellValueFactory(p ->
                    new SimpleStringProperty(p.getValue().getDeparture().format(Constants.DATE_TIME_FORMATTER)));

            TableColumn<Ride, String> seatsColumn = new TableColumn<>("Available seats");
            seatsColumn.setCellValueFactory(p ->
                    new SimpleStringProperty(Integer.toString(service.findEmptySeatsOnRide(p.getValue()))));

            ridesTable.getColumns().setAll(destinationColumn, departureColumn, seatsColumn);
            loadRides();

            ridesTable.getSelectionModel().selectedItemProperty().addListener(event -> {
                Ride ride = ridesTable.getSelectionModel().getSelectedItem();
                if (ride != null) {
                    handleRideSelection(ride);
                }
            });
        });
    }

    public void createReservationsTable() {
        Platform.runLater(() -> {
            TableColumn<ClientSeat, String> seatColumn = new TableColumn<>("Seat");
            seatColumn.setCellValueFactory(p ->
                    new SimpleStringProperty(Integer.toString(p.getValue().getSeat().getSeatNumber())));

            TableColumn<ClientSeat, String> clientColumn = new TableColumn<>("Client");
            clientColumn.setCellValueFactory(p -> {
                if (p.getValue().getClient() == null) {
                    return new SimpleStringProperty("-");
                }
                return new SimpleStringProperty(p.getValue().getClient().getName());
            });

            reservationsTable.getColumns().setAll(seatColumn, clientColumn);
        });
    }

    public void handleRidesFilters() {
        Platform.runLater(() -> ridesTable.setItems(FXCollections.observableList(service
                .findRidesByDestinationAndDeparture(destinationField.getText(), departurePicker.getValue()))));
    }

    public void loadRides() {
        Platform.runLater(() -> ridesTable.setItems(FXCollections.observableList(service.findAllRides())));
    }

    public void loadReservations() {
        Platform.runLater(() -> reservationsTable.setItems(FXCollections.observableArrayList(service
                .findReservationsByRide(selectedRide))));
    }

    public void handleRideSelection(Ride ride) {
        selectedRide = ride;
        destinationText.setText("Destination: " + ride.getDestination());
        departureText.setText("Departure: " + ride.getDeparture().format(Constants.DATE_TIME_FORMATTER));
        loadReservations();
    }

    public void handleReserveButton() {
        Platform.runLater(() -> {
            try {
                service.createReservation(selectedRide, nameField.getText(), phoneField.getText(),
                        Integer.parseInt(seatsCountField.getText()));
            } catch (InvalidDataException ex) {
                utils.raiseError("Reservation Error", ex.getMessage());
            } catch (NumberFormatException ignored) {
                utils.raiseError("Reservation Error", "Invalid number in the seats count text field!");
            }
        });
    }
}
