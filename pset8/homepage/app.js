//features that are were bot yet added//
document.addEventListener('DOMContentLoaded', function() {
    let pop = document.querySelectorAll('.alert');
    for (let i = 0; i < pop.length; i++) {
        pop[i].addEventListener('click', function() {
            alert('Feature not yet implemented');
        });
    }
});

//initializer for the slider//
const initSlider = () => {
    const imageList = document.querySelector(".slider-wrapper .image-list");
    const slidebtns = document.querySelectorAll(".slider-wrapper .slide-btn");
    const sliderScrollBar = document.querySelector(".slider-container .slider-scrollbar");
    const scrollbarThumb = sliderScrollBar.querySelector(".scrollbar-thumb");
    const maxScrollLeft = imageList.scrollWidth -imageList.clientWidth;

    scrollbarThumb.addEventListener("mousedown", (e) => {
        const startx = e.clientx;
    });

    //slide image according to the button clicks//
    slidebtns.forEach(button => {
        button.addEventListener("click", () => {
            const direction = button.id === "prev-btn" ? -1 : 1;
            const scrollAmount = imageList.clientWidth * direction;
            imageList.scrollBy({ left: scrollAmount, behavior: "smooth" });
        });
    });

    const handleSlidebtns = () => {
        slidebtns[0].style.display = imageList.scrollLeft <= 0 ? "none" : "block";
        slidebtns[1].style.display = imageList.scrollLeft >= maxScrollLeft? "none" : "block";
    }

    //upadate scrollbar pos on image scroll//
    const updateScrollThumbPosition = () => {
        const scrollPosition = imageList.scrollLeft;
        const thumbPosition = (scrollPosition / maxScrollLeft) * (sliderScrollBar.clientWidth - scrollbarThumb.offsetWidth);
        scrollbarThumb.style.left = `${thumbPosition}px`;
    }

    imageList.addEventListener("scroll", () => {
        handleSlidebtns();
        updateScrollThumbPosition();
    });
}

window.addEventListener("load", initSlider);
