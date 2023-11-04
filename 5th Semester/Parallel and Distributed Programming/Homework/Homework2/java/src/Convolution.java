public abstract class Convolution {
    protected final int N, M, K, P;
    protected final int[][] matrix, conv;

    public Convolution(int[][] matrix, int[][] conv, int P) {
        N = matrix.length;
        if (N > 0) {
            M = matrix[0].length;
        } else {
            M = 0;
        }
        this.matrix = matrix;
        K = conv.length;
        this.conv = conv;
        this.P = P;
    }

    private int matrixElemExtended(int i, int j) {
        if (i < 0) {
            i = 0;
        } else if (i >= N) {
            i = N - 1;
        }
        if (j < 0) {
            j = 0;
        } else if (j >= M) {
            j = M - 1;
        }
        return matrix[i][j];
    }

    protected int oneConv(int i, int j) {
        int sum = 0;
        for (int p = 0; p < K; ++p) {
            int idx1 = i - K / 2 + p;
            for (int q = 0; q < K; ++q) {
                int idx2 = j - K / 2 + q;
                sum += matrixElemExtended(idx1, idx2) * conv[p][q];
            }
        }
        return sum;
    }

    public abstract int[][] apply();
}

class SequentialConvolution extends Convolution {
    public SequentialConvolution(int[][] matrix, int[][] conv) {
        super(matrix, conv, 0);
    }

    @Override
    public int[][] apply() {
        int[][] answer = new int[N][M];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j){
                answer[i][j] = oneConv(i, j);
            }
        }
        return answer;
    }
}

class LinesBatchConvolution extends Convolution {
    public LinesBatchConvolution(int[][] matrix, int[][] conv, int P) {
        super(matrix, conv, P);
    }

    @Override
    public int[][] apply() {
        int[][] answer = new int[N][M];
        Thread[] threads = new Thread[P];
        int threadId = 0;
        int linesPerThread = N / P;
        int linesLeft = N % P;
        for (int k = 0; k < N; k += linesPerThread) {
            int start = k;
            if (linesLeft > 0) {
                --linesLeft;
                ++k;
            }
            int end = k + linesPerThread - 1;
            threads[threadId] = new Thread(() -> {
                for (int i = start; i <= end; i++) {
                    for (int j = 0; j < M; j++) {
                        answer[i][j] = oneConv(i, j);
                    }
                }
            });
            threads[threadId++].start();
        }
        for (Thread thread : threads) {
            try {
                if (thread != null) {
                    thread.join();
                }
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
        return answer;
    }
}

class LinesCyclicConvolution extends Convolution {
    public LinesCyclicConvolution(int[][] matrix, int[][] conv, int P) {
        super(matrix, conv, P);
    }

    @Override
    public int[][] apply() {
        int[][] answer = new int[N][M];
        Thread[] threads = new Thread[P];
        for (int k = 0; k < P; ++k) {
            int finalK = k;
            threads[k] = new Thread(() -> {
                for (int i = finalK; i < N; i += P) {
                    for (int j = 0; j < M; ++j) {
                        answer[i][j] = oneConv(i, j);
                    }
                }
            });
            threads[k].start();
        }
        for (Thread thread : threads) {
            try {
                if (thread != null) {
                    thread.join();
                }
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
        return answer;
    }
}

class ColumnsBatchConvolution extends Convolution {
    public ColumnsBatchConvolution(int[][] matrix, int[][] conv, int P) {
        super(matrix, conv, P);
    }

    @Override
    public int[][] apply() {
        int[][] answer = new int[N][M];
        Thread[] threads = new Thread[P];
        int threadId = 0;
        int columnsPerThread = M / P;
        int columnsLeft = M % P;
        for (int k = 0; k < M; k += columnsPerThread) {
            int start = k;
            if (columnsLeft > 0) {
                --columnsLeft;
                ++k;
            }
            int end = k + columnsPerThread - 1;
            threads[threadId] = new Thread(() -> {
                for (int j = start; j <= end; j++) {
                    for (int i = 0; i < N; i++) {
                        answer[i][j] = oneConv(i, j);
                    }
                }
            });
            threads[threadId++].start();
        }
        for (Thread thread : threads) {
            try {
                if (thread != null) {
                    thread.join();
                }
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
        return answer;
    }
}

class ColumnsCyclicConvolution extends Convolution {
    public ColumnsCyclicConvolution(int[][] matrix, int[][] conv, int P) {
        super(matrix, conv, P);
    }

    @Override
    public int[][] apply() {
        int[][] answer = new int[N][M];
        Thread[] threads = new Thread[P];
        for (int k = 0; k < P; ++k) {
            int finalK = k;
            threads[k] = new Thread(() -> {
                for (int j = finalK; j < M; j += P) {
                    for (int i = 0; i < N; ++i) {
                        answer[i][j] = oneConv(i, j);
                    }
                }
            });
            threads[k].start();
        }
        for (Thread thread : threads) {
            try {
                if (thread != null) {
                    thread.join();
                }
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
        return answer;
    }
}

class LinearizationBatchConvolution extends Convolution {
    public LinearizationBatchConvolution(int[][] matrix, int[][] conv, int P) {
        super(matrix, conv, P);
    }

    @Override
    public int[][] apply() {
        int[][] answer = new int[N][M];
        Thread[] threads = new Thread[P];
        int threadId = 0;
        int elemsPerThread = N * M / P;
        int elemsLeft = N * M % P;
        for (int k = 0; k < N * M; k += elemsPerThread) {
            int start = k;
            if (elemsLeft > 0) {
                --elemsLeft;
                ++k;
            }
            int end = k + elemsPerThread - 1;
            threads[threadId] = new Thread(() -> {
                for (int idx = start; idx <= end; ++idx) {
                    int i = idx / M;
                    int j = idx % M;
                    answer[i][j] = oneConv(i, j);
                }
            });
            threads[threadId++].start();
        }
        for (Thread thread : threads) {
            try {
                if (thread != null) {
                    thread.join();
                }
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
        return answer;
    }
}

class LinearizationCyclicConvolution extends Convolution {
    public LinearizationCyclicConvolution(int[][] matrix, int[][] conv, int P) {
        super(matrix, conv, P);
    }

    @Override
    public int[][] apply() {
        int[][] answer = new int[N][M];
        Thread[] threads = new Thread[P];
        for (int k = 0; k < P; ++k) {
            int finalK = k;
            threads[k] = new Thread(() -> {
                for (int idx = finalK; idx < N * M; idx += P) {
                    int i = idx / M;
                    int j = idx % M;
                    answer[i][j] = oneConv(i, j);
                }
            });
            threads[k].start();
        }
        for (Thread thread : threads) {
            try {
                if (thread != null) {
                    thread.join();
                }
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
        return answer;
    }
}

class BlockConvolution extends Convolution {
    public BlockConvolution(int[][] matrix, int[][] conv, int P) {
        super(matrix, conv, P);
    }

    @Override
    public int[][] apply() {
        int[][] answer = new int[N][M];
        Thread[] threads = new Thread[P];
        int threadId = 0;
        int totalElems = N * M;
        int elemsPerThread = totalElems / P;
        int elemsLeft = totalElems % P;

        for (int k = 0; k < totalElems; k += elemsPerThread) {
            int startI = k / M, startJ = k % M;
            if (elemsLeft > 0) {
                --elemsLeft;
                ++k;
            }
            int endI = (k + elemsPerThread - 1) / M, endJ = (k + elemsPerThread - 1) % M;
            threads[threadId] = new Thread(() -> {
                int i = startI, j = startJ;
                while (!(i == endI && j == endJ)) {
                    answer[i][j] = oneConv(i, j);
                    ++j;
                    if (j == M) {
                        j = 0;
                        ++i;
                    }
                }
            });
            threads[threadId++].start();
        }
        for (Thread thread : threads) {
            try {
                if (thread != null) {
                    thread.join();
                }
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
        return answer;
    }
}