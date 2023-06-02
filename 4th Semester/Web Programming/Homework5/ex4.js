const sortFn = (table, toSort, swapFn) => {
    let numericalCriteria = true, n = toSort.length;
    if (isNaN(toSort[0])) {
        numericalCriteria = false;
    }
    let sorted = false;
    while (!sorted) {
        sorted = true;
        for (let i = 0; i < n - 1; i++) {
            if (numericalCriteria) {
                if (parseInt(toSort[i]) > parseInt(toSort[i + 1])) {
                    sorted = false;
                    swapFn(table, i, i + 1);
                    [toSort[i], toSort[i + 1]] = [toSort[i + 1], toSort[i]];
                }
            }
            else {
                if (toSort[i] > toSort[i + 1]) {
                    sorted = false;
                    swapFn(table, i, i + 1);
                    [toSort[i], toSort[i + 1]] = [toSort[i + 1], toSort[i]];
                }
            }
        }
        n--;
    }
    if (n === toSort.length - 1) { // in case it's already sorted, we reverse it
        n = toSort.length;
        for (let i = 0; i < n / 2; i++) {
            [toSort[i], toSort[n - i - 1]] = [toSort[n - i -1], toSort[i]];
            swapFn(table, i, n - i - 1);
        }
    }
}

const swapColumns = (table, i, j) => {
    $("tr", table).each(function() {
        let aux = $(this).children().eq(i + 1).html();
        $(this).children().eq(i + 1).html($(this).children().eq(j + 1).html());
        $(this).children().eq(j + 1).html(aux);
    })
}
const sortColumn = (header) => {
    const row = header.parent();
    const table = row.parent().parent();
    let toSort = [];
    let n = row.children().length;
    for (let i = 1; i < n; i++) {
        toSort.push(row.children().eq(i).html());
    }
    sortFn(table, toSort, swapColumns);
}

const swapRows = (table, i, j) => {
    let aux = $(table).find('tr').eq(i + 1).html();
    $(table).find('tr').eq(i + 1).html($(table).find('tr').eq(j + 1).html());
    $(table).find('tr').eq(j + 1).html(aux);
}

const sortRow = (header) => {
    const row = header.parent();
    const table = row.parent().parent();
    let indexHeader = -1;

    table.find("tr:first th").each((i, el) => {
        if ($(el).html() === header.html()) {
            indexHeader = i;
        }
    });

    let toSort = [];
    $(table)
        .find("tr:not(:first)")
        .each((i, row) => {
            toSort.push($(row).find(`td:eq(${indexHeader})`).html());
        });
    sortFn(table, toSort, swapRows);
}

$("#horizontal-table").find("th").click(function() {
    sortColumn($(this));
});
$("#vertical-table").find("tr:first th").click(function() {
    sortRow($(this));
})