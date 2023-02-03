module application.gui {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens application.gui to javafx.fxml;
    exports application.gui;
    exports application.controller;
    opens application.controller to javafx.fxml;
    exports application.models;
    exports application.models.exceptions;
    exports application.repository;
    exports application.service;
}