let currentImageIndex = 0;
const delay = 3000;

const images = $('li');
const showNextImage = (skipPages) => {
    if (typeof skipPages !== 'number') {
        skipPages = 1;
    }
    $(images[currentImageIndex]).hide();
    currentImageIndex = (currentImageIndex + skipPages) % images.length;
    $(images[currentImageIndex]).show();
}

let intervalId = setInterval(showNextImage, delay);
$('#next-button').click(() => {
    showNextImage();
    clearInterval(intervalId);
    intervalId = setInterval(showNextImage, delay);
});

$('#previous-button').click(() => {
    showNextImage(images.length - 1);
    clearInterval(intervalId);
    intervalId = setInterval(showNextImage, delay);
});