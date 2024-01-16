int main() {
    int a = 0, b = 0;
    cout << "Enter the numbers: ";
    cin >> a >> b;
    int res = (a * (a + 1) - b * (b + 1)) / b + 4 * b / a;
    cout << "The result of (" << a << " * (" << a << " + " << 1 << ") - " << b 
        << " * (" << b << " + " << 1 << ")) / " << b << " + " << 4 << " * " << b
        << " / " << a <<  " is " << res << "!\nExtra operation: 5 + 3 = " << 5 + 3 << " :D\n";
}