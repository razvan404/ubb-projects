<?php
    session_start();
    require_once('utils.php');

    function insert_grade($studentid, $subjectid, $grade) {
        $conn = get_new_connection();
        $stmt = $conn->prepare("INSERT INTO students_subjects (student_id, subject_id, grade) VALUES (?, ?, ?)");
        $stmt->bind_param('iii', $studentid, $subjectid, $grade);
        $stmt->execute();

        if ($stmt->affected_rows == -1) {
            $conn->close();
            grade_message("The grade could not be added!");
        }
        $conn->close();
    }

    function main() {
        if (!isset($_SESSION["teacherid"]) || $_SERVER["REQUEST_METHOD"] !== "POST") {
            redirect_to_main_page();
        }
        if (!isset($_POST["teacherid"]) || !isset($_POST["subjectid"]) || !isset($_POST["studentid"]) || !isset($_POST["grade"])) {
            grade_message("Invalid request!");
        }        
        $teacherid = parse_input($_POST["teacherid"]);
        if ($teacherid != $_SESSION["teacherid"]) {
            grade_message("Invalid teacher id setted!");
        }
        $studentid = parse_input($_POST["studentid"]);
        $subjectid = parse_input($_POST["subjectid"]);
        $grade = parse_input($_POST["grade"]);
        insert_grade($studentid, $subjectid, $grade);
        grade_message("Grade inserted successfully!");
    }

    main();
?>