package OnwardTravel.controller;

import OnwardTravel.gui.OnwardTravel;
import OnwardTravel.models.ClientSeat;
import OnwardTravel.models.Ride;
import OnwardTravel.repository.exceptions.DataChangeException;
import OnwardTravel.service.Service;
import OnwardTravel.service.exceptions.InvalidDataException;
import OnwardTravel.utils.Constants;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Text;

import java.io.IOException;

public class MainController {
    private final Service service = ControllerUtils.getService();
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

    public void build() {
        welcomeText.setText("Welcome, " + service.getCurrentUser().getUsername() + "!");
        createRidesTable();
        createReservationsTable();
    }

    @FXML
    public void handleLogOutButton() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(OnwardTravel.class.getResource("login-view.fxml"));
        AnchorPane pane = fxmlLoader.load();
        Scene scene = new Scene(pane);
        ControllerUtils.setScene(scene);
    }

    public void createRidesTable() {
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
    }

    public void createReservationsTable() {
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
    }

    public void handleRidesFilters() {
        ridesTable.setItems(FXCollections.observableList(service.findRidesByDestinationAndDeparture(
                destinationField.getText(), departurePicker.getValue())));
    }

    public void loadRides() {
        ridesTable.setItems(FXCollections.observableList(service.findAllRides()));
    }

    public void loadReservations() {
        reservationsTable.setItems(FXCollections.observableArrayList(service.findReservationsByRide(selectedRide)));
    }

    public void handleRideSelection(Ride ride) {
        selectedRide = ride;
        destinationText.setText("Destination: " + ride.getDestination());
        departureText.setText("Departure: " + ride.getDeparture().format(Constants.DATE_TIME_FORMATTER));
        loadReservations();
    }

    public void handleReserveButton() {
        try {
            service.createReservation(selectedRide, nameField.getText(), phoneField.getText(),
                    Integer.parseInt(seatsCountField.getText()));
            loadReservations();
            loadRides();
        } catch (DataChangeException | InvalidDataException ex) {
            ControllerUtils.raiseError("Reservation Error", ex.getMessage());
        } catch (NumberFormatException ignored) {
            ControllerUtils.raiseError("Reservation Error", "Introduce a number in the seats count text field!");
        }
    }
}
