let usersCount = 0;
let currentPage = 0;
const usersPerPage = 3;
const usersTable = document.getElementById("usersTable");
const prevButton = document.getElementById("prev");
const nextButton = document.getElementById("next");

const getUsersCount = () => {
    fetch("userscount.php")
        .then(response => response.text())
        .then(data => {
            usersCount = +data;
            setButtons();
        });
}

const getUsers = () => {
    fetch("users.php?startIndex=" + (currentPage * usersPerPage) + "&usersCount=" + usersPerPage)
        .then(response => response.text())
        .then(data => usersTable.innerHTML = data);
}

const postUsers = () => {
    const requestOptions = {
        method: "POST",
        headers: {
            "Content-Type": "application/x-www-form-urlencoded"
        },
        body: `startIndex=${departure}&usersCount=${usersPerPage}`
    }
    fetch("users.php", requestOptions)
        .then(response => response.text())
        .then(data => usersTable.innerHTML = data);
}

const methodForGettingUsers = postUsers;

const setButtons = () => {
    if (currentPage == 0) {
        prevButton.disabled = true;
    } else {
        prevButton.disabled = false;
    }
    if (currentPage * (currentPage + 1) > usersCount - 1) {
        nextButton.disabled = true;
    } else {
        nextButton.disabled = false;
    }
}

document.addEventListener("DOMContentLoaded", () => {
    getUsersCount();
    getUsers();
    prevButton.onclick = () => {
        currentPage--;
        getUsers();
        setButtons();
    };
    nextButton.onclick = () => {
        currentPage++;
        getUsers();
        setButtons();
    };
});