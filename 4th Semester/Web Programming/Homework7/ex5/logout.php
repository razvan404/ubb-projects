<?php
    session_start();
    require_once('utils.php');
    session_destroy();
    header('Location: index.php');
?>
