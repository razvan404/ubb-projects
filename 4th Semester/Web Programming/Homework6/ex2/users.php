<?php
    $server = "localhost";
    $db = "labajax";
    
    $departure = "";
    $startidx = 0;
    $count = 0;
    if ($_SERVER["REQUEST_METHOD"] === "GET" && isset($_GET["startIndex"]) && isset($_GET["usersCount"])) {
        $startidx = $_GET["startIndex"];
        $count = $_GET["usersCount"];
    } else if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["startIndex"]) && isset($_POST["usersCount"])) {
        $startidx = $_POST["startIndex"];
        $count = $_POST["usersCount"];
    } else {
        die("Invalid request!");
    }

    $startidx = intval($startidx);
    $count = intval($count);

    $conn = new mysqli($server, "root", "", $db);
    if ($conn->connect_error) {
        die("Connection failed to MySQL ".$conn->connect_error);
    }
    
    $sql = "SELECT * FROM `users` LIMIT $startidx, $count";
    $result = $conn->query($sql);

    echo "<tr><th>ID</th><th>First Name</th><th>Last Name</th><th>Phone</th><th>Email</th></tr>";
    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            $id = $row['user_id'];
            $firstname = $row['first_name'];
            $lastname = $row['last_name'];
            $phone = $row['phone'];
            $email = $row['email'];
            echo "<tr><td>$id</td><td>$firstname</td><td>$lastname</td><td>$phone</td><td>$email</td></tr>";
        }
    }
    $conn->close();
?>