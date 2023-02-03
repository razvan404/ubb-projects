package application.controller;

import application.models.Hotel;
import application.models.HotelType;
import application.models.SpecialOffer;
import application.models.exceptions.ValidationException;
import application.service.Service;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.time.LocalDate;
import java.util.List;

public class SpecialViewController {
    private Service service;
    private Hotel hotel;
    @FXML
    public Label titleLabel;
    @FXML
    public VBox vBox;
    @FXML
    public Text errorText;
    @FXML
    public DatePicker startPicker;
    @FXML
    public DatePicker endPicker;

    private TableView<SpecialOffer> specialTable;

    public void setResources(Service service, Hotel hotel) {
        this.service = service;
        this.hotel = hotel;
    }

    public void build() {
        titleLabel.setText("Hotel " + hotel.getHotelName() + " special offers");
        specialTable = createSpecialOffersTable(service.getSpecialOffersFrom(hotel));
        vBox.getChildren().add(specialTable);
        errorText.setText("");
    }

    private TableView<SpecialOffer> createSpecialOffersTable(List<SpecialOffer> hotels) {
        TableView<SpecialOffer> specialTable = new TableView<>();
        TableColumn<SpecialOffer, LocalDate> startColumn = new TableColumn<>("Start date");
        startColumn.setCellValueFactory(new PropertyValueFactory<>("startDate"));

        TableColumn<SpecialOffer, LocalDate> endColumn = new TableColumn<>("End date");
        endColumn.setCellValueFactory(new PropertyValueFactory<>("endDate"));

        TableColumn<SpecialOffer, Double> priceColumn = new TableColumn<>("Percents");
        priceColumn.setCellValueFactory(new PropertyValueFactory<>("percents"));

        specialTable.getColumns().addAll(startColumn, endColumn, priceColumn);
        specialTable.setItems(FXCollections.observableList(hotels));

        specialTable.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        return specialTable;
    }

    @FXML
    public void handleSearch() {
        try {
            specialTable.setItems(FXCollections
                    .observableList(service.getSpecialOffersBetween(hotel, startPicker.getValue(), endPicker.getValue())));
            errorText.setText("");
        } catch (ValidationException e) {
            errorText.setText(e.getMessage());
        }
    }
}
