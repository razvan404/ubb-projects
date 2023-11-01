#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <functional>
#include <cassert>

using namespace std;

void printArray(int arr[], int N) {
    for (int i = 0; i < N - 1; ++i) {
        cout << arr[i] << ", ";
    }
    cout << arr[N - 1];
}

void cleanArray(int arr[], int N) {
    for (int i = 0; i < N; ++i) {
        arr[i] = 0;
    }
}

double meassureTime(function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
    return elapsedTimeMs;
};

void sum(int A[], int B[], int C[], int start, int end, int step) {
    for (int i = start; i <= end; i += step) {
        C[i] = pow(A[i], 3) + pow(B[i], 3);
    }
}

void sequentialSum(int A[], int B[], int C[], int N) {
    sum(A, B, C, 0, N - 1, 1);
}

void batchSum(int A[], int B[], int C[], int N, int P) {
    int batchPerThread = N / P;
    int unresolvedItems = N % P;
    vector<thread> threads(P);
    int threadIdx = 0;
    for (int i = 0; i < N; i += batchPerThread) {
        int start = i, end = i + batchPerThread - 1;
        if (unresolvedItems) {
            ++end;
            ++i;
            --unresolvedItems;
        }
        threads[threadIdx++] = thread(sum, A, B, C, start, end, 1);
    }
    for (int i = 0; i < P; ++i) {
        threads[i].join();
    }
}

void cyclicSum(int A[], int B[], int C[], int N, int P) {
    vector<thread> threads(P);
    for (int i = 0; i < P; ++i) {
        threads[i] = thread(sum, A, B, C, i, N - 1, P);
    }
    for (int i = 0; i < P; ++i) {
        threads[i].join();
    }
}

const int N = 10000000, P = 30, L = 5;
int A[N], B[N], C[3][N];

int main() {
    
    int* AD = new int[N],
        * BD = new int[N],
        * CD[3]{ new int[N], new int[N], new int[N] };
    for (int i = 0; i < N; ++i) {
        A[i] = rand() % (L + 1);
        B[i] = rand() % (L + 1);
        AD[i] = rand() % (L + 1);
        BD[i] = rand() % (L + 1);
    }
    
    double sequentialTime = meassureTime([&]() {
        sequentialSum(A, B, C[0], N);
        });
    cout << "Time sequential: " << sequentialTime << "ms" << endl;

    double batchTime = meassureTime([&]() {
        batchSum(A, B, C[1], N, P);
        });
    cout << "Time batch: " << batchTime << "ms" << endl;

    double cyclicTime = meassureTime([&]() {
        cyclicSum(A, B, C[2], N, P);
        });
    cout << "Time cyclic: " << cyclicTime << "ms" << endl;

    for (int i = 0; i < N; ++i) {
        assert(C[0][i] == C[1][i]);
        assert(C[0][i] == C[2][i]);
    }

    double sequentialDynamicTime = meassureTime([&]() {
        sequentialSum(AD, BD, CD[0], N);
        });
    cout << "Time sequential dynamic: " << sequentialDynamicTime << "ms" << endl;

    double batchDynamicTime = meassureTime([&]() {
        batchSum(AD, BD, CD[1], N, P);
        });
    cout << "Time batch dynamic: " << batchDynamicTime << "ms" << endl;

    double cyclicDynamicTime = meassureTime([&]() {
        cyclicSum(AD, BD, CD[2], N, P);
        });
    cout << "Time cyclic dynamic: " << cyclicDynamicTime << "ms" << endl;

    for (int i = 0; i < N; ++i) {
        assert(C[0][i] == C[1][i]);
        assert(C[0][i] == C[2][i]);
    }

    delete[] AD;
    delete[] BD;
    for (int i = 0; i < 3; ++i) {
        delete[] CD[i];
    }
}
