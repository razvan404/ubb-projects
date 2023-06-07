package controllers;

import ams.RidesController;
import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import models.Ride;
import services.NotificationReceiver;
import services.ServiceException;
import utils.Constants;

import java.time.LocalDate;
import java.time.LocalDateTime;

public class RidesView {
    @FXML
    public TableView<Ride> ridesTable;
    protected RidesController ctrl;
    protected ObservableList<Ride> rides;
    @FXML
    public TextField destinationField;
    @FXML
    public DatePicker departurePicker;

    public void setController(RidesController ctrl) {
        this.ctrl = ctrl;
        ctrl.setView(this);
        createRidesTable();
    }

    public void createRidesTable() {
        Platform.runLater(() -> {
            TableColumn<Ride, String> destinationColumn = new TableColumn<>("Destination");
            destinationColumn.setCellValueFactory(new PropertyValueFactory<>("destination"));

            TableColumn<Ride, String> departureColumn = new TableColumn<>("Departure");
            departureColumn.setCellValueFactory(p ->
                    new SimpleStringProperty(p.getValue().getDeparture().format(Constants.DATE_TIME_FORMATTER)));

            ridesTable.getColumns().setAll(destinationColumn, departureColumn);
            loadRides();

            ridesTable.getSelectionModel().selectedItemProperty().addListener(event -> {
                Ride ride = ridesTable.getSelectionModel().getSelectedItem();
                if (ride != null) {
                    handleRideSelection(ride);
                }
            });
        });
    }

    public void loadRides() {
        rides = FXCollections.observableList(ctrl.getAllRides());
        ridesTable.setItems(rides);
    }

    public void handleRideSelection(Ride ride) {
        System.out.println(ride);
    }

    public void handleCreateRide() {
        String destination = destinationField.getText();
        LocalDate departure = departurePicker.getValue();
        if (destination == null || destination.equals("")) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Destination is empty");
            alert.setContentText("Please enter a destination");
            alert.showAndWait();
            return;
        }
        else if (departure == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Departure is empty");
            alert.setContentText("Please enter a departure");
            alert.showAndWait();
            return;
        }
        try {
            ctrl.createRide(destination, departure.atStartOfDay());
        } catch (ServiceException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Error creating ride");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
            return;
        }
    }
    public void handleRideCreated(Ride ride) {
        Platform.runLater(() -> {
            System.out.println("Ride created, arrived in View");
            if (!rides.contains(ride)) {
                rides.add(ride);

                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Information");
                alert.setHeaderText("Ride created");
                alert.setContentText("Ride " + ride + " was created");
                alert.showAndWait();
                return;
            }
        });
    }
}
