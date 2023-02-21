package application.controller;

import application.models.Client;
import application.models.Hotel;
import application.models.exceptions.ValidationException;
import application.service.Service;
import application.utils.Constants;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;

import java.time.DateTimeException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class ReservationViewController {
    private Service service;
    private Client client;
    private Hotel hotel;
    public TextField startDateField;
    public TextField noNightsField;
    public Text errorText;
    @FXML
    public Label titleLabel;

    public void setResources(Service service, Client client, Hotel hotel) {
        this.service = service;
        this.client = client;
        this.hotel = hotel;
    }

    public void build() {
        titleLabel.setText("Hotel " + hotel.getHotelName() + " reservation");
        errorText.setText("");
    }

    public void handleReserveButton() {
        try {
            System.out.println("Hello world");
            LocalDateTime startDay = LocalDateTime.parse(startDateField.getText(), Constants.DATE_TIME_FORMATTER);
            int noNights = Integer.parseInt(noNightsField.getText());
            service.reserve(client, hotel, startDay, noNights);
            errorText.setText("");
        } catch (DateTimeException | NumberFormatException | ValidationException e) {
            errorText.setText(e.getMessage());
        }
    }
}
