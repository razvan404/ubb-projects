<?php
    session_start();
    require_once('utils.php');
    $conn = get_new_connection();

    $username = parse_input($_POST['username']);
    $password = parse_input($_POST['password']);

    if ($username == "" || $password == "") {
        $conn->close();
        raise_login_err("You must introduce your username and password!");
    }

    $stmt = $conn->prepare('SELECT * FROM credentials WHERE username = ? AND password = ?');
    $stmt->bind_param('ss', $username, $password);
    $stmt->execute();
    $result = $stmt->get_result()->fetch_all();
    if (count($result) == 0) {
        $conn->close();
        raise_login_err("Invalid credentials!");
    }
    $_SESSION['id'] = $result[0][0];
    $conn->close();
    header('Location: main.php');
?>
