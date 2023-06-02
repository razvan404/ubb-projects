let table = [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '];
let tableDisabled = false;

const disableTable = (text) => {
    tableDisabled = true;
    $("#helperText").html(text);
}

const enableTable = (text) => {
    tableDisabled = false;
    $("#helperText").html(text);
}

const put = (cell) => {
    if (tableDisabled) {
        alert("Wait for your turn!");
        return;
    }
    let i = cell.closest('tr').index();
    let j = cell.index();
    let idx = 3 * i + j;
    if (table[idx] !== " ") {
        alert("Invalid cell. Try again!");
        return;
    }
    cell.html("X");
    table[idx] = "X";
    disableTable("Computer's turn!");
    sendTableToServer();
}

const loadTable = () => {
    $("#table").find("tr").each(function(i) {
        $(this).find("td").each(function(j) {
            $(this).html(table[3 * i + j]);
        })            
    });
}

const processResponse = (response) => {
    responseComponents = response.split('|');
    for (let i = 0; i < 9; i++) {
        table[i] = responseComponents[0][i];
    }
    if (responseComponents.length == 2) {
        if (responseComponents[1] === "x-win") {
            disableTable("You WON!");
            loadTable();
        } else if (responseComponents[1] === "o-win") {
            disableTable("You lost!");
            loadTable();
        } else if (responseComponents[1] === "draw") {
            disableTable("It's a draw!");
            loadTable();
        }
    } else {
        setTimeout(() => {
            loadTable();
            enableTable("Your turn!");
        }, 800);
    }
}

const sendTableToServer = () => {
    $.ajax({
        type: "POST",
        url: "tictactoe.php",
        data: {table: table.join('')},
        success: (response) => {
            processResponse(response);  
        }
    })
}

$(document).ready(() => {
    $("#table td").click(function() {
        put($(this));
    });
    if (Math.random() > 0.5) {
        disableTable("Computer's turn!");
        sendTableToServer();
    } else {
        enableTable("Your turn!");
    }
});