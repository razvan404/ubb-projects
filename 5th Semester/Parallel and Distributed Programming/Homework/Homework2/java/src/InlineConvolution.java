import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public abstract class InlineConvolution {
    protected final int N, M, K, P, halfK;
    protected final int[][] matrix, conv;

    public InlineConvolution(int[][] matrix, int[][] conv, int P) {
        N = matrix.length;
        if (N > 0) {
            M = matrix[0].length;
        } else {
            M = 0;
        }
        this.matrix = matrix;
        K = conv.length;
        halfK = K / 2;
        this.conv = conv;
        this.P = P;
    }

    protected int getElemInCache(int i, int j, int rowIndex, int[][] cache, int[][] endCache) {
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
        if (i > rowIndex) {
            if (endCache == null) {
                return matrix[i][j];
            } else {
                return endCache[i - rowIndex - 1][j];
            }
        }
        return cache[i - rowIndex + halfK][j];
    }

    protected int oneConvWithCache(int i, int j, int[][] cache, int[][] endCache) {
        int sum = 0;
        for (int p = 0; p < K; ++p) {
            int idx1 = i - K / 2 + p;
            for (int q = 0; q < K; ++q) {
                int idx2 = j - K / 2 + q;
                sum += conv[p][q] * getElemInCache(idx1, idx2, i, cache, endCache);
            }
        }
        return sum;
    }

    protected void oneLineConv(int i, int[][] cache, int[][] endCache) {
        for (int j = 0; j < M; ++j) {
            matrix[i][j] = oneConvWithCache(i, j, cache, endCache);
        }
    }

    private int[][] initCache(int start) {
        int[][] cache = new int[halfK + 1][M];
        for (int i = start - halfK; i < start; ++i) {
            if (i < 0) continue;
            if (i >= N) break;
            System.arraycopy(matrix[i], 0, cache[i - start + halfK + 1], 0, M);
        }
        return cache;
    }

    private int[][] initEndCache(int end) {
        int[][] endCache = new int[Math.min(halfK, N - end - 1)][M];
        for (int i = end + 1; i <= end + halfK; ++i) {
            if (i < 0) continue;
            if (i >= N) break;
            System.arraycopy(matrix[i], 0, endCache[i - end - 1], 0, M);
        }
        return endCache;
    }

    private void shiftCache(int[][] cache, int newLine) {
        shiftCache(cache, newLine, matrix);
    }

    private void shiftCache(int[][] cache, int newLine, int[][] source) {
        for (int i = 0; i < halfK; ++i) {
            System.arraycopy(cache[i + 1], 0, cache[i], 0, M);
        }
        if (newLine < source.length) {
            System.arraycopy(source[newLine], 0, cache[halfK], 0, M);
        }
    }

    protected void manyLinesConv(int start, int end) {
        int[][] cache = initCache(start);
        for (int i = start; i <= end; ++i) {
            shiftCache(cache, i);
            oneLineConv(i, cache, null);
        }
    }

    protected void manyLinesConvParallel(int start, int end, CyclicBarrier cyclicBarrier) {
        int[][] cache = initCache(start);
        int[][] endCache = initEndCache(end);
        int endThreshold = end - halfK + 1;
        try {
            cyclicBarrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            throw new RuntimeException(e);
        }
        for (int i = start; i <= end; ++i) {
            shiftCache(cache, i);
            if (i >= endThreshold) {
                oneLineConv(i, cache, endCache);
            } else {
                oneLineConv(i, cache, null);
            }
        }
    }

    public abstract int[][] apply();
}

class InlineSequentialConvolution extends InlineConvolution {
    public InlineSequentialConvolution(int[][] matrix, int[][] conv) {
        super(matrix, conv, 1);
    }

    @Override
    public int[][] apply() {
        manyLinesConv(0, N - 1);
        return this.matrix;
    }
}

class InlineLinesConvolution extends InlineConvolution {
    public InlineLinesConvolution(int[][] matrix, int[][] conv, int P) {
        super(matrix, conv, P);
    }

    @Override
    public int[][] apply() {
        Thread[] threads = new Thread[P];
        CyclicBarrier cyclicBarrier = new CyclicBarrier(P);
        int linesPerThread = N / P;
        int linesRemaining = N % P;
        int threadId = 0;
        for (int i = 0; i < N; i += linesPerThread) {
            int start = i;
            if (linesRemaining > 0) {
                ++i;
                --linesRemaining;
            }
            int end = i + linesPerThread - 1;
            threads[threadId] = new Thread(() -> manyLinesConvParallel(start, end, cyclicBarrier));
            threads[threadId++].start();
        }
        for (var thread : threads) {
            if (thread != null) {
                try {
                    thread.join();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
        return this.matrix;
    }
}