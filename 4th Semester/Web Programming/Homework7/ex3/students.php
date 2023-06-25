<?php
    session_start();
    require_once('utils.php');
?>

<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Student grades</title>
    <style>
        * {
            font-size: 20px;
        }
        table, th, td {
            border: 1px solid black;
        }
    </style>
</head>
<body>
    <fieldset>
        <legend><strong>Student grades</strong></legend>
        <table>
            <?php
                if (!isset($_GET["firstName"]) || !isset($_GET["lastName"])) {
                    redirect_to_main_page();
                }
                $firstname = parse_input($_GET["firstName"]);
                $lastname = parse_input($_GET["lastName"]);
                $conn = get_new_connection();
                $stmt = $conn->prepare("SELECT stud.student_id, subj.name, ss.grade, ss.submitted_at FROM students stud 
                                        INNER JOIN students_subjects ss ON stud.student_id = ss.student_id
                                        INNER JOIN subjects subj ON subj.subject_id = ss.subject_id 
                                        WHERE stud.first_name = ? AND stud.last_name = ?");
                $stmt->bind_param('ss', $firstname, $lastname);
                $stmt->execute();
                $result = $stmt->get_result();
                if ($result->num_rows == 0) {
                    raise_stud_err("Invalid student's first name / last name.");
                }
                echo "<tr><th>Student ID</th><th>Subject</th><th>Grade</th><th>Submitted at</th></tr>";
                while ($row = $result->fetch_assoc()) {
                    $id = $row['student_id'];
                    $subject = $row['name'];
                    $grade = $row['grade'];
                    $at = $row['submitted_at'];
                    echo "<tr><td>$id</td><td>$subject</td><td>$grade</td><td>$at</td></tr>";
                }
            ?>
        </table>
    </fieldset>  
</body>
</html>