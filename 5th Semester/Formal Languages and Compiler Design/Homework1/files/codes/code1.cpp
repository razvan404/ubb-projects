double pi = 3.141592;

struct Circle {
    double radius;
    double perimeter;
    double area;
};

int main() {
    struct Circle circle;
    std::cout << "Enter the radius of the circle: ";
    std::cin >> circle.radius;
    if (circle.radius < 0) {
        std::cout << "Invalid radius!";
    } else {
        circle.perimeter = 2 * pi * circle.radius;
        circle.area = pi * circle.radius * circle.radius;
        std::cout << "Perimeter of the circle: " << perimeter << "\n";
        std::cout << "Area of the circle: " << area << "\n";
    }
}