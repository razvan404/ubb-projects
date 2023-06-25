<?php
  session_start();
  if (isset($_SESSION['id'])) {
    header("Location: main.php");
    die();
  }
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Login Page</title>
  <style>
    * {
      font-size: 20px;
    }
  </style>
</head>
<body>
  <fieldset>
    <legend><strong>Login</strong></legend>
    <form action="login.php" method="post">          
      <label for="username">Username:</label>
      <input type="text" name="username" id="username"><br>
      <label for="password">Password:</label>      
      <input type="password" name="password" id="password"><br>
      <?php
        if (isset($_GET["loginError"])) {
          echo "<p>".$_GET["loginError"]."</p>";
        }
      ?>
      <input type="submit" value="Login">
    </form>
  </fieldset>
</body>
</html>