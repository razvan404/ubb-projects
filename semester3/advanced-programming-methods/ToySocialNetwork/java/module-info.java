module application.gui {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires java.sql;

    opens application.gui to javafx.fxml;
    exports application.gui;
    exports application.gui.controller;
    exports application.gui.controller.windows;
    exports application.gui.controller.list;
    exports application.service;
    exports application.service.exceptions;
    exports application.repository;
    exports application.models;
    exports application.models.notification;
    exports application.models.exceptions;
    exports application.utils;
    exports application.utils.pair;
}