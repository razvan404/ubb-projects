<?php
    session_start();
    require_once('utils.php');
    $userid = $_SESSION["id"];
    $imageid = $_GET["id"];
    if (isset($userid) && isset($imageid)) {
        if ($imageid == "") {
            die("bruh");
        }
        $imageid = parse_input($imageid);
        $conn = get_new_connection();
        $stmt = $conn->prepare('SELECT image FROM images WHERE user_id = ? AND id = ?');
        $stmt->bind_param('ss', $userid, $imageid);
        $stmt->execute();
        $result = $stmt->get_result()->fetch_all();
        if (count($result) != 0) {
            $image_path = $result[0][0];
            unlink($image_path);
            $stmt = $conn->prepare('DELETE FROM images WHERE id = ?');
            $stmt->bind_param('s', $imageid);
            $stmt->execute();
        }
    }
    header('Location: main.php');
?>