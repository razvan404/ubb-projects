<?php
    function parse_input($data) {
        return trim(htmlspecialchars(stripslashes($data)));
    }

    function get_new_connection() {
        $server = "localhost";
        $db = "labajax";

        $conn = new mysqli($server, "root", "", $db);
        if ($conn->connect_error) {
            die("Connection failed to MySQL ".$conn->connect_error);
        }
        return $conn;
    }

    function raise_login_err($text) {
        header("Location: index.php?loginError=$text");
        die();
    }

    function raise_search_err($text) {
        header("Location: main.php?searchError=$text");
        die();
    }

    function raise_upload_err($text) {
        header("Location: main.php?uploadError=$text");
        die();
    }
?>