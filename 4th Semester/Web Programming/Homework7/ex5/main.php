<?php
    session_start();
    require_once('utils.php');
    
    function get_images($id) {
        $conn = get_new_connection();
        $stmt = $conn->prepare('SELECT id, image FROM images WHERE user_id = ?');
        $stmt->bind_param('s', $id);
        $stmt->execute();
        $result = $stmt->get_result()->fetch_all();
        $conn->close();
        return $result;
    }
?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Main page</title>
    <style>
        * {
            font-size: 20px;
        }
        h1 {
            font-size: 30px;
        }
        h2 {
            font-size: 25px;
        }
        .imgContainer {
            display: flex; 
            flex-direction: row; 
            flex-wrap: wrap;
        }
        .imgDiv {
            display: flex; 
            flex-direction: column; 
            align-items: center;
        }
        img {
            width: 150px; 
            height: 150px;
        }
    </style>
</head>
<body>
    
</body>
</html>
    <fieldset>
        <legend><strong><h1>Main Page</h1></strong></legend>
        <?php
            $id = $_SESSION['id'];

            if (!$id) {
                raise_login_err("You are not logged in!");
            }

            $images = get_images($id);
            echo "<h1>Your images</h1>";
            echo "<div class='imgContainer'>";
            foreach ($images as $image)
            {
                echo "<div class='imgDiv'>";
                echo "<img src='".$image[1]."' alt='".$image[0]."' style=''>";
                echo "<a href='delete.php?id=".$image[0]."'>Delete</a>";
                echo "</div>";
            }
            echo "</div>";

            echo "<hr><form action='add.php' method='post' enctype='multipart/form-data'>";
            echo "<label for='file'><h1>Upload an image</h1></label><input type='file' name='file' id='file' accept='image/*'><br><br>";
            echo "<input type='submit' value='Upload'>";
            echo "</form>";

            if (isset($_GET['uploadError'])) {
                echo "<p>".$_GET['uploadError']."</p>";
            }

            echo "<hr><form action='main.php' method='get'>";
            echo "<label for='username'><h1>Search user's photos</h1></label><input type='text' name='search' id='username'><br><br>";
            echo "<input type='submit' value='Search'>";
            echo "</form>";
        

            if (isset($_GET['searchError'])) {
                echo "<p>".$_GET['searchError']."</p>";
            }

            if(isset($_GET['search'])) {
                $conn = get_new_connection();
                $username = $_GET['search'];
                $stmt = $conn->prepare('SELECT id FROM credentials WHERE username = ?');
                $stmt->bind_param('s', $username);
                $stmt->execute();
                $result = $stmt->get_result()->fetch_all();
                if (count($result) == 0) {
                    raise_search_err("There was no user found!");
                }

                $id = $result[0][0];
                $stmt = $conn->prepare('SELECT image FROM images WHERE user_id = ?');
                $stmt->bind_param('s', $id);
                $stmt->execute();
                $images = $stmt->get_result()->fetch_all();
                
                echo "<h2>Images of $username</h2>";
                echo "<div class='imgContainer'>";
                foreach ($images as $image) {
                    echo "<div class='imgDiv'>";
                    echo "<img alt='".$image[0]."' src='".$image[0]."'>";
                    echo "</div>";
                }
                echo "</div>";
                $conn->close();
            }

            echo "<hr><a href='logout.php'>Logout</a>";
        ?>
    </fieldset>
</html>
</body>
