<?php
    //session_start();
    require_once('utils.php');
    session_destroy();
    raise_login_err("Successfully logged out!");
?>