#pragma warning (disable: 4996)
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;

//int** MATRIX, ** CONV, ** ANSWER;
const int LIMIT = 10000;
int MATRIX[LIMIT][LIMIT], CONV[LIMIT][LIMIT], ANSWER[LIMIT][LIMIT];

class Convolution {
protected:
    int N, M, K, P;
private:
    int matrixElemExtended(int i, int j) const {
        if (i < 0) {
            i = 0;
        }
        else if (i >= N) {
			i = N - 1;
		}
        if (j < 0) {
			j = 0;
		}
		else if (j >= M) {
            j = M - 1;
        }
        return MATRIX[i][j];
    }
protected:
    int oneConv(int i, int j) const {
        int sum = 0;
        for (int p = 0; p < K; p++) {
            int idx = i + p - K / 2;
            for (int q = 0; q < K; q++) {
				sum += matrixElemExtended(idx, j + q - K / 2) * CONV[p][q];
			}
		}
		return sum;
    }
public:
    Convolution(int n, int m, int k, int p) {
        N = n;
        M = m;
        K = k;
        P = p;
    }
	virtual void apply() const = 0;
};

class SequentialConvolution : public Convolution {
public:
    SequentialConvolution(int n, int m, int k) : Convolution(n, m, k, 1) {}
    
    void apply() const override {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
				ANSWER[i][j] = oneConv(i, j);
			}
		}
    }
};

class LinesBatchConvolution : public Convolution {
public:
    LinesBatchConvolution(int n, int m, int k, int p) : Convolution(n, m, k, p) {}
    
    void apply() const override {
        vector<thread*> threads(P);
        int threadId = 0;
        int linesPerThread = N / P;
        int linesLeft = N % P;
        for (int k = 0; k < N; k += linesPerThread) {
            int start = k;
            if (linesLeft) {
                --linesLeft;
                ++k;
            }
            int end = k + linesPerThread - 1;
            threads[threadId++] = new thread([start, end, this]() {
                for (int i = start; i <= end; i++) {
                    for (int j = 0; j < M; j++) {
                        ANSWER[i][j] = oneConv(i, j);
                    }
                }
            });
        }
        for (int i = 0; i < P; i++) {
            if (threads[i] != nullptr) {
				threads[i]->join();
                delete threads[i];
			}
		}
    }
};

class LinesCyclicConvolution : public Convolution {
public:
    LinesCyclicConvolution(int n, int m, int k, int p) : Convolution(n, m, k, p) {}

    void apply() const override {
        vector<thread*> threads(P);
        for (int k = 0; k < P; k++) {
            int finalK = k;
            threads[k] = new thread([finalK, this]() {
                for (int i = finalK; i < N; i += P) {
                    for (int j = 0; j < M; j++) {
						ANSWER[i][j] = oneConv(i, j);
					}
				}
			});
		}
        for (int i = 0; i < P; i++) {
            if (threads[i] != nullptr) {
                threads[i]->join();
                delete threads[i];
            }
        }
    }
};

class ColumnsBatchConvolution : public Convolution {
public:
    ColumnsBatchConvolution(int n, int m, int k, int p) : Convolution(n, m, k, p) {}

    void apply() const override {
        vector<thread*> threads(P);
		int threadId = 0;
		int columnsPerThread = M / P;
		int columnsLeft = M % P;
        for (int k = 0; k < M; k += columnsPerThread) {
			int start = k;
            if (columnsLeft) {
				--columnsLeft;
				++k;
			}
			int end = k + columnsPerThread - 1;
            threads[threadId++] = new thread([start, end, this]() {
                for (int j = start; j <= end; j++) {
                    for (int i = 0; i < N; i++) {
						ANSWER[i][j] = oneConv(i, j);
					}
				}
			});
		}
		for (int i = 0; i < P; i++) {
            if (threads[i] != nullptr) {
				threads[i]->join();
				delete threads[i];
			}
        }
    }
};

class ColumnsCyclicConvolution : public Convolution {
public:
    ColumnsCyclicConvolution(int n, int m, int k, int p) : Convolution(n, m, k, p) {}

    void apply() const override {
    	vector<thread*> threads(P, nullptr);
        for (int k = 0; k < P; k++) {
			int finalK = k;
            threads[k] = new thread([finalK, this]() {
                for (int j = finalK; j < M; j += P) {
                    for (int i = 0; i < N; i++) {
                        ANSWER[i][j] = oneConv(i, j);
                    }
                }
                });
        }
        for (int i = 0; i < P; i++) {
            if (threads[i] != nullptr) {
                threads[i]->join();
                delete threads[i];
            }
		}
    }
};

class LinearizationBatchConvolution : public Convolution {
public:
    LinearizationBatchConvolution(int n, int m, int k, int p) : Convolution(n, m, k, p) {}

    void apply() const override {
        vector<thread*> threads(P);
		int threadId = 0;
        int totalElems = N * M;
		int elemsPerThread = totalElems / P;
		int elemsLeft = totalElems % P;
        for (int k = 0; k < totalElems; k += elemsPerThread) {
			int start = k;
            if (elemsLeft) {
				--elemsLeft;
				++k;
			}
			int end = k + elemsPerThread - 1;
            threads[threadId++] = new thread([start, end, this]() {
                for (int idx = start; idx <= end; idx++) {
					int i = idx / M;
                    int j = idx % M;
                    ANSWER[i][j] = oneConv(i, j);
				}
			});
		}
		for (int i = 0; i < P; i++) {
        	threads[i]->join();
		}
    }
};

class LinearizationCyclicConvolution : public Convolution {
public:
    LinearizationCyclicConvolution(int n, int m, int k, int p) : Convolution(n, m, k, p) {}

    void apply() const override {
		vector<thread*> threads(P);
        int totalElems = N * M;
        for (int k = 0; k < P; k++) {
            int finalK = k;
            threads[k] = new thread([finalK, totalElems, this]() {
                for (int idx = finalK; idx < totalElems; idx += P) {
                    int i = idx / M;
                    int j = idx % M;
                    ANSWER[i][j] = oneConv(i, j);
                }
                });
        }
        for (int i = 0; i < P; i++) {
            if (threads[i] != nullptr) {
				threads[i]->join();
				delete threads[i];
			}
        }
    }
};

class BlockConvolution : public Convolution {
public:
    BlockConvolution(int n, int m, int k, int p) : Convolution(n, m, k, p) {}

    void apply() const override {
        vector<thread*> threads(P);
		int threadId = 0;
        int totalElems = N * M;
		int elemsPerThread = totalElems / P;
		int elemsLeft = totalElems % P;
        for (int k = 0; k < totalElems; k += elemsPerThread) {
            int startI = k / M, startJ = k % M;
            if (elemsLeft) {
                ++k;
                --elemsLeft;
            }
            int endI = (k + elemsPerThread - 1) / M, endJ = (k + elemsPerThread - 1) % M;
            threads[threadId++] = new thread([startI, startJ, endI, endJ, this]() {
                int i = startI, j = startJ;
                while (!(i == endI && j == endJ)) {
					ANSWER[i][j] = oneConv(i, j);
					++j;
                    if (j == M) {
						j = 0;
						++i;
					}
				}
			});
        }
        
        for (int i = 0; i < P; i++) {
            if (threads[i] != nullptr) {
				threads[i]->join();
				delete threads[i];
			}
		}
    }
};



tuple<int, int, int> readFromFile(string filename) {
    FILE* fin = fopen(filename.c_str(), "r");
    int n, m, k;
    fscanf(fin, "%d%d", &n, &m);
    //MATRIX = new int* [n];
    //ANSWER = new int* [n];
    for (int i = 0; i < n; i++) {
        //MATRIX[i] = new int[m];
        //ANSWER[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            fscanf(fin, "%d", MATRIX[i] + j);
        }
    }
    fscanf(fin, "%d", &k);
    //CONV = new int* [k];
    for (int i = 0; i < k; i++) {
        //CONV[i] = new int[k];
        for (int j = 0; j < k; ++j) {
            fscanf(fin, "%d", CONV[i] + j);
        }
    }
    fclose(fin);
    return { n, m, k };
}

void writeToFile(string filename, int N, int M) {
    FILE* fout = fopen(filename.c_str(), "w");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M - 1; ++j) {
			fprintf(fout, "%d ", ANSWER[i][j]);
		}
        fprintf(fout, "%d\n", ANSWER[i][M - 1]);
	}
	fclose(fout);
}

string BASE_DIR = "../../files/";
string INPUT_DIR = BASE_DIR + "inputs/";
string OUTPUT_DIR = BASE_DIR + "outputs/";

int main(int argc, char* argv[])
{
    if (argc < 3 || argc > 5) {
        cout << "Usage: " << argv[0] << " <input file> <method> [<parallelism method> <number of threads>]" << endl;
		return 1;
    }

    string inputFilename = INPUT_DIR + argv[1];
    auto tuple = readFromFile(inputFilename);
    int n = get<0>(tuple), m = get<1>(tuple), k = get<2>(tuple);
    string outputFilename = OUTPUT_DIR;

    Convolution* conv = nullptr;
    string method = argv[2];
    if (method == "sequential") {
		conv = new SequentialConvolution(n, m, k);
        outputFilename += method + "_" + to_string(n) + "_" + to_string(m) + "_" + to_string(k) + ".txt";
	}
    else if (method == "block") {
        int p = stoi(argv[3]);
        conv = new BlockConvolution(n, m, k, p);
        outputFilename += method + "_" + to_string(n) + "_" + to_string(m) + "_" + to_string(k) + "_" + to_string(p) + ".txt";
    }
    else {
        string parallelismMethod = argv[3];
        int p = stoi(argv[4]);
        if (parallelismMethod != "batch" && parallelismMethod != "cyclic") {
            cout << "Unknown parallelism method " << parallelismMethod << endl;
            return 1;
        }
        if (method == "lines") {
            if (parallelismMethod == "batch") {
                conv = new LinesBatchConvolution(n, m, k, p);
            }
            else {
                conv = new LinesCyclicConvolution(n, m, k, p);
            }
        }
        else if (method == "columns") {
            if (parallelismMethod == "batch") {
                conv = new ColumnsBatchConvolution(n, m, k, p);
            }
            else {
                conv = new ColumnsCyclicConvolution(n, m, k, p);
            }
        }
        else if (method == "linearization") {
            if (parallelismMethod == "batch") {
                conv = new LinearizationBatchConvolution(n, m, k, p);
            }
            else {
                conv = new LinearizationCyclicConvolution(n, m, k, p);
            }
        }
        outputFilename += method + "_" + parallelismMethod + "_" + to_string(n) + "_" + to_string(m) + "_" + to_string(k) + "_" + to_string(p) + ".txt";
    }

    if (conv == nullptr) {
        cout << "Error at convolution initialization!\nMethod " << method << " unknown!" << endl;
        return 1;
    }
    auto start = chrono::high_resolution_clock::now();
    conv->apply();
    auto end = chrono::high_resolution_clock::now();
    double elapsedTimeMs = chrono::duration<double, milli>(end - start).count();
    cout << elapsedTimeMs << endl;
    writeToFile(outputFilename, n, m);
    delete conv;
    for (int i = 0; i < n; i++) {
        //delete[] MATRIX[i];
        //delete[] ANSWER[i];
    }
    //delete[] MATRIX;
    //delete[] ANSWER;
    for (int i = 0; i < k; i++) {
		//delete[] CONV[i];
	}
    //delete[] CONV;

    return 0;
}
