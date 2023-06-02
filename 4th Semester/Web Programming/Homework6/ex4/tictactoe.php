<?php
    if ($_SERVER['REQUEST_METHOD'] !== 'POST' || !isset($_POST["table"])) {
        die('Invalid request');    
    }
    $table = str_split($_POST["table"]);
    $winner = ' ';

    function checkWinner($table) {
        for ($i = 0; $i < 3; $i++) {
            if ($table[$i * 3] !== ' ' && $table[$i * 3 + 1] === $table[$i * 3] && $table[$i * 3 + 2] === $table[$i * 3]) {
                return $table[$i * 3];
            }
            if ($table[$i] !== ' ' && $table[$i + 3] === $table[$i] && $table[$i + 6] === $table[$i]) {
                return $table[$i];
            }
        }

        if ($table[0] !== ' ' && $table[4] === $table[0] && $table[8] === $table[0]) {
            return $table[0];
        }
        if ($table[2] !== ' ' && $table[4] === $table[2] && $table[6] === $table[2]) {
            return $table[2];
        }
        for ($i = 0; $i < 9; $i++) {
            if ($table[$i] === ' ') {
                return ' ';
            }
        }
        return '/';
    }

    function sendResponseIfGameOver($table, $winner) {
        switch ($winner) {
            case '/':
                exit(join('', $table)."|draw");
            case 'X':
                exit(join('', $table)."|x-win");
            case 'O':
                exit(join('', $table)."|o-win");
            default:
                break;
        }
    }

    $winner = checkWinner($table);
    sendResponseIfGameOver($table, $winner);
    do {
        $index = rand(0, 8);
    } while($table[$index] !== ' ');
    $table[$index] = "O";
    $winner = checkWinner($table); 
    sendResponseIfGameOver($table, $winner);
    exit(join('', $table));
?>