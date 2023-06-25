<?php
    require_once('utils.php');

    function get_trains($from, $to) {
		$conn = get_new_connection();

		if (isset($_GET['direct'])) {
			$stmt = $conn->prepare('SELECT * FROM trains WHERE start = ? AND stop = ?');
			$stmt->bind_param('ss', $from, $to);
			$stmt->execute();
			$result = $stmt->get_result();
			if ($result->num_rows > 0) {
				echo "Curse directe de la $from la $to: <br>";
				$table = "<table> <tr><th>Nr. tren</th> <th>Start</th> 
					<th>Ora plecare</th><th>Stop</th><th>Ora sosire</th> </tr>";
	
				while ($row = $result->fetch_assoc()) {
					$table .= "<tr><td>".$row["trainNo"]."</td>"
						."<td>".$row["start"]."</td>"."<td>".$row["dHour"]
						."<td>".$row["stop"]."</td>"."</td>"."<td>".$row["aHour"]." </td></tr>";
				}
				$table .= "</table>";
				echo $table;
			} else {
				echo "Nu sunt curse directe pentru ruta $from - $to!";
			}
		}
	
		echo "<br>";
		if (isset($_GET['inter'])) {
			$stmt = $conn->prepare('SELECT T1.trainNo, T1.start, T1.stop, T1.dHour, T1.aHour, T2.stop as stop2,
											T2.dHour as dHour2, T2.aHour as aHour2 FROM trains T1 INNER JOIN 
											trains T2 ON T1.stop = T2.start  
											WHERE T1.start = ? AND T2.stop = ?');
			$stmt->bind_param('ss', $from, $to);
			$stmt->execute();
	
			$result = $stmt->get_result();
			if ($result->num_rows > 0) {
				echo "Curse cu legatura de la $from la $to : <br>";
				$table = "<table> <tr><th>Nr. tren</th><th>Start</th><th>Ora plecare 1</th> 
					<th>Stop 1</th><th>Ora sosire 1</th><th>Ora plecare 2 </th> 
					<th>Stop 2</th><th>Ora sosire 2</th>
					</tr>";
				while ($row = $result->fetch_assoc()) {
					$table .= "<tr><td>".$row["trainNo"]."</td>"."<td>".$row["start"]."</td>"
						."<td>".$row["dHour"]."</td>"."<td>".$row["stop"]."</td>"
						."<td>".$row["aHour"]."</td>"."<td>".$row["dHour2"]."</td>"
						."<td>".$row["stop2"]."</td>"."<td>".$row["aHour2"]."</td></tr>";
				}
				$table .= "</table>";
				echo $table;
			} else {
				echo "Nu exista curse cu legatura pentru ruta $from - $to!";
			}
		}
    }
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Trains</title>
	<style>
		* {
			font-size: 20px;
		}
		h1 {
			font-size: 30px;
		}
		table, tr, td, th {
            border: 1px black solid;
        }
	</style>
</head>
<body>
	<fieldset>
		<legend><h1>Firma de trenuri</h1></legend>
		<form method="get" action="index.php">
			<label for="start">De la: </label>
			<input type="text" name="start"><br>
			<label for="stop">Până la: </label>
			<input type="text" name="stop" id="stop"><br>
			<label>Tip:</label>
			<input type="checkbox" name="direct">Cursă directă</input>
			<input type="checkbox" name="inter">Cursă cu legatură</input><br>
			<input type="submit" value="Caută trenuri">
		</form>
		<?php	
			if (!isset($_GET["start"]) || !isset($_GET["stop"])) {
				return;
			}
			$start = $_GET["start"];
			$stop = $_GET["stop"];
			$start = parse_input($start);
			$stop = parse_input($stop);
			$good = true;
			if ($start == "" || $stop == "") {
				echo "<p>Selectează de unde și până unde vrei să ajungi!</p>";
				$good = false;
			}
			if (!isset($_GET["direct"]) && !isset($_GET["inter"])) {
				echo "<p>Selectează minim un tip!</p>";
				$good = false;
			}
			if (!$good) {
				return;
			}
			get_trains($start, $stop);
		?>
	</fieldset>
</body>
</html>
	
