<?php
    session_start();
    require_once('utils.php');

    $id = $_SESSION['id'];
    if (!$id) {
        raise_login_err("You need to login first!");
    }

    function get_comentarii() {
        $conn = get_new_connection();
        $stmt = $conn->prepare('SELECT id, autor, text, accepted FROM comentarii ORDER BY id DESC');
        $stmt->execute();
        return $stmt->get_result()->fetch_all();
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Admin Page</title>
    <style>
        .accepted {
            border: lime 5px solid;
        }
        .rejected {
            border: red 5px solid;
        }
    </style>
</head>
<body>
    <fieldset>
        <legend><h2>Comentarii</h2></legend>
        <?php
            $comentarii = get_comentarii();
            foreach ($comentarii as $comentariu) {
                $class = '';
                if($comentariu[3] == 1) {
                    $class = 'accepted';
                }
                else if($comentariu[3] == 2) {
                    $class = 'rejected';
                }    
                
                echo '<fieldset class="'.$class.'"><legend><h3>'.$comentariu[1].'</h3></legend><p>'.$comentariu[2].'</p>';
                echo '<form action="approve.php" method="post">';
                echo '<input type="hidden" name="id" value="'.$comentariu[0].'">';
                echo '<input type="hidden" name="accepted" value="1">';
                echo '<input type="submit" value="Accept">';
                echo '</form>';
                echo '<form action="approve.php" method="post">';
                echo '<input type="hidden" name="id" value="'.$comentariu[0].'">';
                echo '<input type="hidden" name="accepted" value="2">';
                echo '<input type="submit" value="Reject">';
                echo '</form>';
                echo '</fieldset>';
            }
        ?>
        <br><hr>
        <a href="index.php">Go back to the article</a><br>
        <a href="logout.php">Logout</a>
    </fieldset>
</body>
</html>