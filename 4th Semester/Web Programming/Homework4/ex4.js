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
    for (let k = 0; k < table.rows.length; k++) {
        let aux = table.rows[k].cells[i + 1].innerHTML;
        table.rows[k].cells[i + 1].innerHTML = table.rows[k].cells[j + 1].innerHTML;
        table.rows[k].cells[j + 1].innerHTML = aux;
    }
}
const sortColumn = (header) => {
    const row = header.parentNode;
    const table = row.parentNode.parentNode;
    let toSort = [];
    let n = row.cells.length;
    for (let i = 1; i < n; i++) {
        toSort.push(row.cells[i].innerHTML);
    }

    sortFn(table, toSort, swapColumns);
}

const swapRows = (table, i, j) => {
    let aux = table.rows[i + 1].innerHTML;
    table.rows[i + 1].innerHTML = table.rows[j + 1].innerHTML;
    table.rows[j + 1].innerHTML = aux;
}

const sortRow = (header) => {
    const row = header.parentNode;
    const table = row.parentNode.parentNode;
    let indexHeader = -1, n = table.rows[0].cells.length;
    for (let i = 0; i < n; i++) {
        if (table.rows[0].cells[i] === header) {
            indexHeader = i;
            break;
        }
    }
    let toSort = [];
    for (let i = 1; i < table.rows.length; i++) {
        toSort.push(table.rows[i].cells[indexHeader].innerHTML);
    }
    sortFn(table, toSort, swapRows);
}