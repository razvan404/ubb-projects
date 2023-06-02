let boardLocked = false;
let firstCard = null, secondCard = null;
let pairsLeft = 8;

const flipCard = (card) => {
    if (boardLocked || card === firstCard) return;
    card.children(':first').removeClass('covered').addClass('uncovered');
    if (firstCard === null) {
        firstCard = card;
        return;
    }
    secondCard = card;
    checkMatch();
}
const checkMatch = () => {
    firstCard.children(':first').html() === secondCard.children(':first').html() ?
        disableCards() : unflipCards();
}
const disableCards = () => {
    firstCard.addClass('right').on('click', false);
    secondCard.addClass('right').on('click', false);
    resetBoard();
    pairsLeft--;
    if (pairsLeft % 4 === 0) {
        setTimeout(() => {
            alert('You won!');
        }, 200)
    }
}
const unflipCards = () => {
    boardLocked = true;
    firstCard.addClass('wrong');
    secondCard.addClass('wrong');
    setTimeout(() => {
        firstCard.children(':first').removeClass().removeClass().addClass('covered');
        secondCard.children(':first').removeClass().removeClass().addClass('covered');
        resetBoard();
    }, 2000);
}
const resetBoard = () => {
    boardLocked = false;
    firstCard = null;
    secondCard = null;
}

$('.card').click(function() {
    flipCard($(this));
});
$('.card div').addClass('covered');
$('.card p').addClass('covered');