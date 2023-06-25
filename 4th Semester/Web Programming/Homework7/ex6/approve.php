<?php
    session_start();
    require_once('utils.php');
    $id = $_SESSION["id"];
    if (!$id) {
        raise_login_err("You need to login first!");
    }

    if (!isset($_POST['accepted']) || !isset($_POST['id'])) {
        header('Location: admin.php');
        die();
    }

    $accepted = parse_input($_POST['accepted']);
    $commentid = parse_input($_POST['id']);

    if (!is_numeric($accepted) || !is_numeric($commentid)) {
        header('Location: admin.php');
        die();
    }

    $conn = get_new_connection();
    $stmt = $conn->prepare('UPDATE comentarii SET accepted = ? WHERE id = ?');
    $stmt->bind_param('ii', $accepted, $commentid);
    $stmt->execute();
    header('Location: admin.php');
?>