int main() {
    int x, y;
    cout << "Enter two numbers: ";
    cin >> x >> y;
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }
    cout << "GCD = " << x << "\n";
}