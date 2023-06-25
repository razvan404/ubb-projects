<?php
    require_once('utils.php');
    function get_comentarii() {
        $conn = get_new_connection();
        $stmt = $conn->prepare('SELECT autor, text FROM comentarii WHERE accepted = 1 ORDER BY id DESC');
        $stmt->execute();
        return $stmt->get_result()->fetch_all();
    }
?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Check pufos</title>
</head>
<body>
    <fieldset>
        <legend><h1>Reteta chec pufos</h1></legend>
        <?php
            include 'articol.php';
            echo '<hr><h3>Comentarii</h3>';
            $comentarii = get_comentarii();
            if(!$comentarii) {
                echo '<p>Nu exista comentarii</p>';
            }
            else {
                foreach ($comentarii as $comentariu) {
                    echo '<fieldset><legend><h3>'.$comentariu[0].'</h3></legend><p>'.$comentariu[1].'</p></fieldset>';
                }
            }
            echo '<hr><h3>Adauga comentariu</h3>';
            echo '<form action="add.php" method="post">';
            echo '<label for="autor">Autor:</label>';
            echo '<input type="text" name="autor" id="autor"><br>';
            echo '<label for="text">Text: </label>';
            echo '<textarea name="text" id="text" cols="30" rows="5"></textarea><br>';
            echo '<input type="submit" value="Trimite">';
            echo '</form>';
            if (isset($_GET["error"])) {
                echo "<p>".$_GET["error"]."</p>";
            }
            echo '<hr><a href="loginPage.php">Login as administrator</a><br>';
        ?>
    </fieldset>
</body>
</html>
<?php    
    
?>
