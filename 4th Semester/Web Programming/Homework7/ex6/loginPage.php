<?php
  session_start();
  if (isset($_SESSION["id"])) {
    header("Location: admin.php");
    die();
  }
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login as administrator</title>
</head>
<body>
  <fieldset>
    <legend><h2>Login as administrator</h2></legend>
    <form action="login.php" method="post">
      <label for="username">Username:</label>
      <input type="text" name="username" id="username"><br>
      <label for="password">Password:</label>
      <input type="password" name="password" id="password"><br>
      <input type="submit" value="Login">
    </form>
    <?php
      if (isset($_GET["loginError"])) {
        echo "<p>".$_GET["loginError"]."</p>";
      }
    ?>
    <a href="index.php">Go back to the article!</a>
  </fieldset>
</body>
</html>