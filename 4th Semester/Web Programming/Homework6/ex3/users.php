<?php
    $server = "localhost";
    $db = "labajax";

    if ($_SERVER['REQUEST_METHOD'] !== 'GET' || !isset($_GET['userId'])) {
        die('Invalid request');    
    }

    $id = $_GET["userId"];

    $conn = new mysqli($server, "root", "", $db);
    if ($conn->connect_error) {
        die("Connection failed to MySQL ".$conn->connect_error);
    }

    $sql = "SELECT * FROM `users` WHERE user_id = \"$id\"";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        if ($row = $result->fetch_assoc()) {
            $firstname = $row['first_name'];
            $lastname = $row['last_name'];
            $phone = $row['phone'];
            $email = $row['email'];
            echo "<label>First name: </label>";
            echo "<input type='text' name='firstName' value='$firstname' />";
            echo "<br>";
            echo "<label>Last name: </label>";
            echo "<input type='text' name='lastName' value='$lastname' />";
            echo "<br>";
            echo "<label>Phone: </label>";
            echo "<input type='number' name='phone' value='$phone' />";
            echo "<br>";
            echo "<label>Email: </label>";
            echo "<input type='email' name='email' value='$email' />";
            echo "<br>";
            echo "<input id='saveBtn' type='submit' value='Save' disabled />";
        }
    }
    $conn->close();
?>