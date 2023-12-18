int main() {
    double pi = 3;
    struct Circle {
        double radius;
        double perimeter;
        double area;
    };
    struct Circle circle;
    cout << "Enter the radius of the circle: ";
    cin >> circle.radius;
    if (circle.radius < 0) {
        cout << "Invalid radius!";
    } else {
        circle.perimeter = 2 * pi * circle.radius;
        circle.area = pi * circle.radius * circle.radius;
        cout << "Perimeter of the circle: " << perimeter << '\n';
        cout << "Area of the circle: " << area << '\n';
    }
}