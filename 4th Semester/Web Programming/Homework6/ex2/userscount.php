<?php
    $server = "localhost";
    $db = "labajax";

    if ($_SERVER['REQUEST_METHOD'] !== 'GET') {
        die('Invalid request');    
    }

    $conn = new mysqli($server, "root", "", $db);
    if ($conn->connect_error) {
        die("Connection failed to MySQL ".$conn->connect_error);
    }

    $sql = "SELECT COUNT(*) AS users_count FROM `users`";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        if ($row = $result->fetch_assoc()) {
            $departure = $row['users_count'];
            echo $departure;
        }
    }
    $conn->close();
?>