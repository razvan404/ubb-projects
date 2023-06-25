<?php
    function parse_input($data) {
        return trim(htmlspecialchars(stripslashes($data)));
    }

    function redirect_to_main_page() {
        header("Location: http://localhost/labphp/ex3");
        die();
    }

    function raise_login_err($text) {
        header("Location: http://localhost/labphp/ex3?loginError=$text");
        die();
    }

    function raise_stud_err($text) {
        header("Location: http://localhost/labphp/ex3?studentError=$text");
        die();
    }

    function grade_message($text) {
        header("Location: http://localhost/labphp/ex3/teachers.php?gradeMsg=$text");
        die();
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
?>