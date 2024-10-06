module tasks {
    requires javafx.graphics;
    requires javafx.controls;
    requires javafx.fxml;
    requires org.controlsfx.controls;
    requires log4j;


    opens tasks.view to javafx.fxml;
    exports tasks.view;
    opens tasks.controller to javafx.fxml;
    exports tasks.controller;
    opens tasks.model;
    exports tasks.model;
    opens tasks.services;
    exports tasks.services;
}
