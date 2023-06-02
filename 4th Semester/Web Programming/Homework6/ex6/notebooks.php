<?php
    $server = "localhost";
    $db = "labajax";
    
    $columns = array("producer", "cpu", "ram", "memory", "gpu");
    $filterby = "";
    $filterval = "";
    $count = 0;
    if ($_SERVER["REQUEST_METHOD"] !== "GET") {
        die("Invalid request!");
    }
    if (isset($_GET["filterBy"]) && isset($_GET["filterValue"])) {
        $filterby = $_GET["filterBy"];
        $filterval = $_GET["filterValue"];
    }
    if ($filterby !== '' && !in_array($filterby, $columns)) {
        die("Invalid request!");
    }

    $conn = new mysqli($server, "root", "", $db);
    if ($conn->connect_error) {
        die("Connection failed to MySQL ".$conn->connect_error);
    }
    
    $sql = "SELECT * FROM `notebooks`";
    if ($filterby !== "") {
        if (is_numeric($filterval)) {
            $sql .= " WHERE $filterby = \"$filterval\"";
        } else {
            $sql .= " WHERE $filterby LIKE \"%$filterval%\"";
        }
    }
    $result = $conn->query($sql);

    echo "<tr><th>Producer</th><th>CPU</th><th>RAM</th><th>Memory</th><th>GPU</th></tr>";
    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            $producer = $row['producer'];
            $cpu = $row['cpu'];
            $ram = $row['ram'];
            $memory = $row['memory'];
            $gpu = $row['gpu'];
            echo "<tr><td>$producer</td><td>$cpu</td><td>$ram</td><td>$memory</td><td>$gpu</td></tr>";
        }
    }
    $conn->close();
?>