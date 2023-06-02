const shuffle = (array) => {
    array.sort(() => Math.random() - 0.5);
}

const isSolvable = (array, n) => {
    let count = 0;
    for (let i = 0; i < n * n; i++) {
        for (let j = 0; j < n * n; j++) {
            if (array[i] > array[j]) {
                count++;
            }
        }
    }
    return count % 2 === 0;
}

const table = document.getElementById('puzzle-table');
const tbody = table.children[0];

const n = 4;
const cells = [];
let coords = [];
let emptyIndex;

for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
        coords.push({x: j, y: i});
    }
}
do {
    shuffle(coords);
} while (!isSolvable(coords));

for (let i = 0; i < n; i++) {
    const row = document.createElement('tr');
    for (let j = 0; j < n; j++) {
        const coord = coords[i * n + j];
        const cell = document.createElement('td');
        if (coord.x === n - 1 && coord.y === n - 1) {
            cell.classList.add('empty');
            emptyIndex = i * n + j;
            cells.push({cell: cell, val: -1});
        } else {
            cell.style.backgroundPosition = '-' + coord.x * 100 + 'px -' + coord.y * 100 + 'px';
            cells.push({cell: cell, val: coord.x + coord.y * n});
        }
        row.appendChild(cell);
    }
    tbody.appendChild(row);
}

document.onkeydown = (ev) => {
    let newIndex = emptyIndex;
    switch (ev.code) {
        case 'ArrowUp':
            if (emptyIndex >= n) newIndex -= n;
            break;
        case 'ArrowDown':
            if (emptyIndex <= n * (n - 1)) newIndex += n;
            break;
        case 'ArrowLeft':
            if (emptyIndex % n !== 0) newIndex -= 1;
            break;
        case 'ArrowRight':
            if (emptyIndex % n !== n - 1) newIndex += 1;
            break;
        default:
            return;
    }
    if (newIndex !== emptyIndex) {
        const emptyCell = cells[emptyIndex].cell;
        const newCell = cells[newIndex].cell;

        cells[emptyIndex].val = cells[newIndex].val;
        cells[newIndex].val = -1;

        emptyCell.innerHTML = newCell.innerHTML;
        newCell.innerHTML = '';
        emptyCell.style.backgroundPosition = newCell.style.backgroundPosition;
        emptyCell.classList.remove('empty');
        newCell.classList.add('empty');
        emptyIndex = newIndex;

        for (let i = 0; i < n * n - 1; i++) {
            console.log(i, cells[i].val);
            if (cells[i].val !== i) {
                return;
            }
        }
        setTimeout(() => {
            alert('You won!');
        }, 200);
    }
}