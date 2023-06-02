const getFilteredNotebooks = (filterBy, filterValue) => {
    $.ajax({
        type: "GET",
        url: "notebooks.php?filterBy=" + filterBy + "&filterValue=" + filterValue,
        success: response => $("#notebooksTable").html(response)
    })
}

const getAllNotebooks = () => {
    $.ajax({
        type: "GET",
        url: "notebooks.php",
        success: response => $("#notebooksTable").html(response)
    });
}

$(document).ready(() => {
    getAllNotebooks();
    $("#clearFilters").click(getAllNotebooks);
    $("#filterNotebooks").submit(function(ev) {
        ev.preventDefault();
        filterBy = $(this)[0][0].value;
        filterValue = $(this)[0][1].value;
        if (filterValue === "") {
            alert("Please enter a filtering value!");
            return;
        }
        getFilteredNotebooks(filterBy, filterValue);
    })
});