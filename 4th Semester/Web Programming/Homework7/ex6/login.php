<?php
    session_start();
    require_once('utils.php');
    
    if (!isset($_POST["username"]) || !isset($_POST["password"])) {
        header("Location: loginPage.php");
        die();
    }

    $username = parse_input($_POST['username']);
    $password = parse_input($_POST['password']);

    if ($username == "" || $password == "") {
        raise_login_err("Please enter an username and a password!");
    }

    $conn = get_new_connection();
    $stmt = $conn->prepare('SELECT id FROM credentials WHERE username = ? AND password = ?');
    $stmt->bind_param('ss', $username, $password);

    $stmt->execute();
    $result = $stmt->get_result()->fetch_all();
    if (count($result) == 0) {
        $conn->close();
        raise_login_err("Invalid credentials!");
    }
    $_SESSION['id'] = $result[0][0];
    header('Location: admin.php');
    $conn->close();
?>


