<?php
    $server = "localhost";
    $db = "labajax";

    if ($_SERVER['REQUEST_METHOD'] !== 'POST' || !isset($_POST['userId']) || !isset($_POST['firstName'])
            || !isset($_POST['lastName']) || !isset($_POST['phone']) || !isset($_POST['email'])) {
        die('Invalid request');    
    }

    $id = $_POST["userId"];
    $firstname = $_POST['firstName'];
    $lastname = $_POST['lastName'];
    $phone = $_POST['phone'];
    $email = $_POST['email'];

    $conn = new mysqli($server, "root", "", $db);
    if ($conn->connect_error) {
        die("Connection failed to MySQL ".$conn->connect_error);
    }

    $sql = "UPDATE `users` SET first_name = \"$firstname\", last_name = \"$lastname\", phone = \"$phone\",
             email = \"$email\" WHERE user_id = \"$id\"";
    if ($conn->query($sql) === TRUE) {
        echo "Record updated successfully!";
    } else {
        echo "Error updating record: $conn->error";
    }

    $conn->close();
?>