
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Trains</title>
    <style>
        * {
            font-size: 20px;
        }
        table, tr, td, th {
            border: 1px black solid;
        }
    </style>
</head>
<body>
    <?php
        $start = parse_input($_POST['start']);
        $stop = parse_input($_POST['stop']);
        
    ?>
</body>
</html>
<?php


getTrains($start, $stop);

echo "</body>
</html>";

function getTrains($from, $to) {
    $servername = "localhost";
    $username = "root";
    $password = "";

    $conn = new mysqli($servername, $username, $password);
    if ($conn->connect_error) {
        die("Cannot connect to the database");
    }

    $sql = "USE lab7";
    if ($conn->query($sql) === TRUE) {

    } else {
        die("Database error");
    }
	if(isset($_POST['direct'])){
		$stmt=$conn->prepare('SELECT * FROM trains WHERE start = ? AND stop = ?');
		$stmt->bind_param('ss', $from, $to);
        $stmt->execute();
        $result = $stmt->get_result();
		if ($result->num_rows > 0) {
            $table = "<table> <tr><th>Nr. tren</th> <th>Tip tren</th> <th> Start</th> 
                <th>Stop</th> <th>Ora plecare</th> <th>Ora sosire</th> </tr>";

            while ($row = $result->fetch_assoc()) {
                $table .= "<tr> <td>" . $row["trainNo"] . "</td>" . "<td>" . $row["trainType"] . " </td>"
                    . "<td>" . $row["start"] . " </td>" . "<td>" . $row["stop"] . " </td>"
                    . "<td>" . $row["dHour"] . " </td>" . "<td>" . $row["aHour"] . " </td></tr>";
            }
            $table .= "</table>";
            echo $table;
        } else {
            echo "Nu sunt curse directe pentru ruta specificata!";
        }
    }

    echo "<br>";
	if (isset($_POST['inter'])) {
        $stmt = $conn->prepare('SELECT T1.trainNo, T1.start,T1.stop,T1.dHour,T1.aHour,T2.stop as stop2,
                                        T2.dHour as d, T2.aHour as a FROM trains T1 INNER JOIN 
                                        trains T2 ON T1.stop = t2.start WHERE t1.start = ? AND t2.stop = ?');
        $stmt->bind_param('ss', $from, $to);
        $stmt->execute();

        $result1 = $stmt->get_result();
        if ($result1->num_rows > 0) {
            $table = "<table> <tr><th>Nr. tren</th> <th> Start</th> 
                <th>Stop 1</th> <th>Ora plecare 1</th> <th>Ora sosire 1</th> 
                <th>Stop 2</th> <th>Ora plecare 2 </th> <th>Ora sosire 2</th>
                </tr>";
            while ($row1 = $result1->fetch_assoc()) {
                $table .= "<tr> <td>" . $row1["trainNo"] . "</td>"
                    . "<td>" . $row1["start"] . " </td>" . "<td>" . $row1["stop"] . " </td>"
                    . "<td>" . $row1["dHour"] . " </td>" . "<td>" . $row1["aHour"] . " </td>"
                    . "<td>" . $row1["stop2"] . "</td>" . "<td>" . $row1["d"] . "</td>"
                    . "<td>" . $row1["a"] . "</td></tr>";
            }
            $table .= "</table>";
            echo $table;
        } else {
            echo "Nu exista curse cu legatura pentru ruta specificata!";
        }
    }
    $conn->close();
}