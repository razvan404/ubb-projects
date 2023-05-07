module OnwardTravel.gui {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires org.apache.logging.log4j;

    opens OnwardTravel.controller to javafx.fxml;
    exports OnwardTravel.controller;
    exports OnwardTravel.gui;
    opens OnwardTravel.gui to javafx.fxml;
    exports OnwardTravel.models;
    opens OnwardTravel.models to javafx.fxml;
    exports OnwardTravel.repository;
    opens OnwardTravel.repository to javafx.fxml;
    exports OnwardTravel.repository.exceptions;
    opens OnwardTravel.repository.exceptions to javafx.fxml;
    exports OnwardTravel.service;
    opens OnwardTravel.service to javafx.fxml;
    exports OnwardTravel.service.exceptions;
    opens OnwardTravel.service.exceptions to javafx.fxml;
}