let currentImageIndex = 0;
const delay = 3000;

const imagesList = document.getElementById('image-list');
const images = imagesList.getElementsByTagName('li');

const showNextImage = (skipPages) => {
    if (typeof skipPages !== 'number') {
        skipPages = 1;
    }

    images[currentImageIndex].style.opacity = '0';
    images[currentImageIndex].style.display = 'none';
    currentImageIndex = (currentImageIndex + skipPages) % images.length;
    images[currentImageIndex].style.opacity = '1';
    images[currentImageIndex].style.display = 'block';
}

let intervalId = setInterval(showNextImage, delay);

const nextButton = document.getElementById('next-button');
const previousButton = document.getElementById('previous-button');
nextButton.onclick = () => {
    showNextImage();
    clearInterval(intervalId);
    intervalId = setInterval(showNextImage, delay);
};

previousButton.onclick = () => {
    showNextImage(images.length - 1);
    clearInterval(intervalId);
    intervalId = setInterval(showNextImage, delay);
};