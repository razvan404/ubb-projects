let usersCount = 0;
let currentPage = 0;
const usersPerPage = 3;

const getUsersCount = () => {
    $.ajax({
        type: "GET",
        url: "userscount.php",
        success: (response) => {
            usersCount = +response;
            setButtons();
        }
    });
}

const getUsers = () => {
    $.ajax({
        type: "GET",
        url: "users.php?startIndex=" + (currentPage * usersPerPage) + "&usersCount=" + usersPerPage,
        success: (response) => {
            $("#usersTable").html(response);
        }
    })
}

const postUsers = () => {
    $.ajax({
        type: "POST",
        url: "users.php",
        data: {startIndex: currentPage * usersPerPage, usersCount: usersPerPage},
        success: (response) => {
            $("#usersTable").html(response);
        }
    })
}

const methodForGettingUsers = getUsers;

const setButtons = () => {
    if (currentPage == 0) {
        $("#prev").prop("disabled", true);
    } else {
        $("#prev").prop("disabled", false);
    }
    if (currentPage * (currentPage + 1) > usersCount - 1) {
        $("#next").prop("disabled", true);
    } else {
        $("#next").prop("disabled", false);
    }
}

$(document).ready(() => {
    getUsersCount();
    methodForGettingUsers();
    $("#prev").click(() => {
        currentPage--;
        methodForGettingUsers();
        setButtons();
    });
    $("#next").click(() => {
        currentPage++;
        methodForGettingUsers();
        setButtons();
    });
});