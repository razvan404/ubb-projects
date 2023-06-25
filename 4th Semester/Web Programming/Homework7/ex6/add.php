<?php
    require_once('utils.php');

    if (!isset($_POST['autor']) || !isset($_POST['text'])) {
        raise_comment_err("Invalid request!");
    }

    $autor = parse_input($_POST['autor']);
    $text = parse_input($_POST['text']);

    if ($autor == "" || $text == "") {
        raise_comment_err("An author name and a text is required!");
    }

    $conn = get_new_connection();
    $stmt = $conn->prepare('INSERT INTO comentarii (autor, text, accepted) VALUES (?, ?, 0)');
    $stmt->bind_param('ss', $autor, $text);
    $stmt->execute();

    raise_comment_err("Comentariu adaugat cu succes, trebuie sa astepti aprobarea unui administrator!");
?>
