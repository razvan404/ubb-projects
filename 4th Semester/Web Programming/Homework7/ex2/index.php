<?php
    require_once("utils.php");
    
    function validate($pag, $n) {
        if (!is_numeric($pag) || !is_numeric($n)) {
            echo "Invalid input, it must be numeric.";
            return false;
        }

        if ($pag != (int)$pag || $n != (int)$n) {
            echo "Invalid input, it must be an integer.";
            return false;
        }

        if ($pag < 0 || $n < 0) {
            echo "Invalid input, it must pe positive.";
            return false;
        }
        return true;
    }
    
    function get_notebooks($pag, $n) {
        $conn = get_new_connection();
        $stmt = $conn->prepare("SELECT producer, cpu, ram, memory, gpu FROM notebooks LIMIT ?, ?");
        $stmt->bind_param("ii", $pag, $n);
        $stmt->execute();
        $result = $stmt->get_result()->fetch_all();
        $conn->close();
        return $result;
    }

    function print_data($data) {
        echo "<table><tr><th>Producer</th><th>CPU</th><th>RAM</th><th>Memory</th><th>GPU</th></tr>";
        foreach ($data as $row) {
            $producer = $row[0];
            $cpu = $row[1];
            $ram = $row[2];
            $memory = $row[3];
            $gpu = $row[4];
            echo "<tr><td>$producer</td><td>$cpu</td><td>$ram</td><td>$memory</td><td>$gpu</td></tr>";
        }
        echo "</table>";
    }

    function print_form($n): void {
        echo "<form action='index.php' method='get'>";
        echo "<input type='hidden' name='pag' value='0'>";
        echo "<label for='n'>Enter the number of entries per page:</label>";
        echo "<input type='number' name='n' value='$n' min='0'><br>";
        echo "<input type='submit' value='Submit'>";
        echo "</form>";
    }
?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Notebooks</title>
    <style>
        * {
            font-size: 20px;
        }
        h1 {
            font-size: 30px;
        }
        table, td, th {
            border: 1px black solid;
        }
    </style>
</head>
<body>
    <fieldset>
        <legend><h1>Find notebooks</h1></legend>
        <?php
            if (!isset($_GET["pag"])) {
                $_GET["pag"] = 0;
            }
            if (!isset($_GET["n"])) {
                $_GET["n"] = 3;
            }

            $pag = $_GET["pag"];
            $n = $_GET["n"];

            if (!validate($pag, $n)) {
                return;
            }
            
            $notebooks = get_notebooks($pag, $n);
            print_form($n);
            print_data($notebooks);

            $next = $pag + $n;
            $prev = $pag - $n;

            if($pag > 0) {
                echo "<a href='index.php?pag=$prev&n=$n'>Previous</a>";
            }
            echo "||";
            if(count($notebooks) - $n == 0) {
                echo "<a href='index.php?pag=$next&n=$n'>Next</a>";
            }
        ?>
    </fieldset>    
</body>
</html>
