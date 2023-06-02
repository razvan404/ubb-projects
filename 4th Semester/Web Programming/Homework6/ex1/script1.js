const departures = document.getElementById("departures");
const destinations = document.getElementById("destinations");

const getDepartures = (departure) => {
    fetch("destinations.php?departure=" + departure)
        .then(response => response.text())
        .then(data => destinations.innerHTML = data)
        .catch(error => console.error(error));
}

const postDepartures = (departure) => {
    const requestOptions = {
        method: "POST",
        headers: {
            "Content-Type": "application/x-www-form-urlencoded"
        },
        body: `departure=${departure}`
    }
    fetch("destinations.php", requestOptions)
        .then(response => response.text())
        .then(data => destinations.innerHTML = data)
        .catch(error => console.error(error));
}

document.addEventListener("DOMContentLoaded", () => {
    fetch("departures.php")
        .then(response => response.text())
        .then(data => departures.innerHTML = data)
        .catch(error => console.error(error));
    departures.onclick = function() {
        const value = this.value;
        postDepartures(value);
    }
})