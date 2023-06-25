<?php
    session_start();
    require_once('utils.php');

    $id = $_SESSION['id'];
    if (!isset($id)) {
        raise_login_err("You are not logged in!");
    }

    $target_dir = './uploads/';
    $target_file = $target_dir . basename($_FILES["file"]["name"]);
    $uploadOk = 1;
    $image_file_type = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));

    if(isset($_POST["submit"])) {
        if(getimagesize($_FILES["file"]["tmp_name"]) == false) {
            raise_upload_err("File is not an image!");
        }
    }

    // renaming the file if already exists
    if (file_exists($target_file)) {
        $filename_without_ext = pathinfo($target_file, PATHINFO_FILENAME);
        $target_file = $target_dir . $filename_without_ext . rand(0, 9) . '.' . $image_file_type;
    }

    if ($_FILES["file"]["size"] > 256000) {
        raise_upload_err("Your file is too large!");
    }

    if($image_file_type != "jpg" && $image_file_type != "png" && $image_file_type != "jpeg" && $image_file_type != "gif" ) {
        raise_upload_err("File type invalid, only JPG, JPEG, PNG & GIF files are allowed! Your file: ".$target_file);
    }

    // rename target file with underscore instead of spaces
    $target_file = str_replace(' ', '_', $target_file);

    if (move_uploaded_file($_FILES["file"]["tmp_name"], $target_file)) {
        echo "The file ". htmlspecialchars( basename( $_FILES["file"]["name"])). " has been uploaded.";
    } else {
        raise_upload_err("There was an error uploading your file.");
    }
    $conn = get_new_connection();
    $stmt = $conn->prepare('INSERT INTO images (user_id, image) VALUES (?, ?)');
    $stmt->bind_param('ss', $id, $target_file);
    $stmt->execute();

    raise_upload_err("Upload successful!");
?>