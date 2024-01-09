int main() {
    int n, x, sum = 0;
    cout << "Give the number of elements: ";
    cin >> n;
    cout << "Give the " << n <<  " elements: ";
    for (int i = 0; i < n; i = i + 1) {
        cin >> x;
        sum = sum + x;
    }
    cout << "The sum is: " << sum << "\n";
}