int main() {
    int n, x, sum = 0;
    std::cout << "Give the number of elements: ";
    std::cin >> n;
    std::cout << "Give the " << n <<  " elements: ";
    for (int i = 0; i < n; i += 1) {
        std::cin >> x;
        sum = sum + x;
    }
    std::cout << "The sum is: " << sum << "\n";
}