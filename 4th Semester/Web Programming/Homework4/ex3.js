let boardLocked = false;
let firstCard = null, secondCard = null;
let pairsLeft = 4;
const flipCard = (card) => {
    if (boardLocked || card === firstCard) return;
    card.children[0].className = 'uncovered';
    if (firstCard === null) {
        firstCard = card;
        return;
    }
    secondCard = card;
    checkMatch();
}
const checkMatch = () => {
    console.log(firstCard.children[0], secondCard.children[0]);
    firstCard.children[0].innerHTML === secondCard.children[0].innerHTML ?
        disableCards() : unflipCards();
}
const disableCards = () => {
    firstCard.classList.add('right');
    secondCard.classList.add('right');
    firstCard.onclick = null;
    secondCard.onclick = null;
    resetBoard();
    pairsLeft--;
    if (pairsLeft === 0) {
        setTimeout(() => {
            alert('You won!');
        }, 200)
    }
}
const unflipCards = () => {
    boardLocked = true;
    firstCard.classList.add('wrong');
    secondCard.classList.add('wrong');
    setTimeout(() => {
        firstCard.children[0].className = 'covered';
        secondCard.children[0].className = 'covered';
        firstCard.classList.remove('wrong');
        secondCard.classList.remove('wrong');
        resetBoard();
    }, 2000);
}
const resetBoard = () => {
    boardLocked = false;
    firstCard = null;
    secondCard = null;
}