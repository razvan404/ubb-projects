int main() {
    int x, y;
    std::cout << "Enter two numbers: ";
    std::cin >> x >> y;
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }
    std::cout << "GCD = " << x << "\n";
}