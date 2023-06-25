<?php
    session_start();
    $_SESSION["teacherid"] = null;
?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>School</title>
    <style>
        * {
            font-size: 20px;
        }
    </style>
</head>
<body>
    <fieldset>
        <legend><strong>Search student grades</strong></legend>
        <form action="students.php" method="get">
            <label for="firstName">First name: </label>
            <input name="firstName" id="firstName" /><br/>
            <label for="lastName">Last name: </label>
            <input name="lastName" id="lastName" /><br/>
            <input type="submit" value="Search" />
        </form>
        <?php
            if (isset($_GET['studentError'])) {
                echo "<p>Invalid student data!</p>";
            }
        ?>
    </fieldset>
    <fieldset>
        <legend><strong>Login as teacher</strong></legend>
        <form action="teachers.php" method="post">
            <label for="username">Username: </label>
            <input name="username" id="username" /><br/>
            <label for="password">Password: </label>
            <input name="password" id="password" type="password"/><br/>
            <input type="submit" value="Login" />
        </form>
        <?php
            if (isset($_GET['loginError'])) {
                echo '<p>'.$_GET['loginError'].'</p>';
            }
        ?>
    </fieldset>
</body>
</html>