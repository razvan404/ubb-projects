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

    $sql = "SELECT DISTINCT departure FROM `routes`";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            $departure = $row['departure'];
            echo "<option value=$departure>$departure</option>";
        }
    }
    $conn->close();
?>