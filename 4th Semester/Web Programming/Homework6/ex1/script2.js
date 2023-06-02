const getDepartures = (departure) => {
    $.ajax({
        type: "GET",
        url: "destinations.php?departure=" + departure,
        success: (response) => {
            $("#destinations").html(response);
        }
    })
}

const postDepartures = (departure) => {
    $.ajax({
        type: "POST",
        url: "destinations.php",
        data: {departure: departure},
        success: (response) => {
            $("#destinations").html(response);
        }
    })
}

$(document).ready(() => {
    $.ajax({
        type: "GET",
        url: "departures.php",
        success: (data, status) => {
            $("#departures").html(data);
        }
    });
    $("#departures").change(function() {
        var value = $(this).val();
        getDepartures(value[0]);
    })
});