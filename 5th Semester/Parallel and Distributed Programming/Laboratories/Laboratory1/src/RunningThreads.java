import java.util.Arrays;
import java.util.Random;

public class RunningThreads {
    public static void cleanUp(int[] out, int N) {
        for (int i = 0; i < N; ++i) {
            out[i] = 0;
        }
    }
    public static double measureTimeInMs(Runnable runnable) {
        long start = System.nanoTime();
        runnable.run();
        long end = System.nanoTime();
        return (end - start) * 1e-6;
    }

    public static void sumElements(int[] in1, int[] in2, int[] out, int start, int end, int step) {
        for (int i = start; i <= end; i += step) {
            out[i] = in1[i] + in2[i];
        }
    }

    public static void runSequentially(int[] in1, int[] in2, int[] out, int N) {
        sumElements(in1, in2, out, 0, N - 1, 1);
    }

    public static class BatchSumThread extends Thread {
        private final int[] in1, in2, out;
        private final int start, end;
        public BatchSumThread(int[] in1, int[] in2, int[] out, int start, int end) {
            this.in1 = in1;
            this.in2 = in2;
            this.out = out;
            this.start = start;
            this.end = end;
        }

        @Override
        public void run() {
            sumElements(in1, in2, out, start, end, 1);
        }
    }

    public static void runInBatches(int[] in1, int[] in2, int[] out, int N, int P) {
        int elemsPerBatch = N / P;
        int elemRemaining = N % P;
        Thread[] threads = new Thread[P];
        int threadId = 0;
        for (int i = 0; i < N; i += elemsPerBatch) {
            int start = i;
            int end = i + elemsPerBatch - 1;
            if (elemRemaining > 0) {
                --elemRemaining;
                ++end;
                ++i;
            }
            threads[threadId] = new BatchSumThread(in1, in2, out, start, end);
            threads[threadId++].start();
        }
        for (int i = 0; i < P; ++i) {
            try {
                threads[i].join();
            } catch (InterruptedException ex) {
                System.err.println(ex.getMessage());
            }
        }
    }

    public static class CyclicSumThread extends Thread {
        private final int[] in1, in2, out;
        private final int start, end, step;

        public CyclicSumThread(int[] in1, int[] in2, int[] out, int start, int end, int step) {
            this.in1 = in1;
            this.in2 = in2;
            this.out = out;
            this.start = start;
            this.end = end;
            this.step = step;
        }

        @Override
        public void run() {
            sumElements(in1, in2, out, start, end, step);
        }
    }

    public static void runCyclic(int[] in1, int[] in2, int[] out, int N, int P) {
        Thread[] threads = new Thread[P];
        for (int i = 0; i < P; ++i) {
            threads[i] = new CyclicSumThread(in1, in2, out, i, N - 1, P);
            threads[i].start();
        }
        for (int i = 0; i < P; ++i) {
            try {
                threads[i].join();
            } catch (InterruptedException ex) {
                System.err.println(ex.getMessage());
            }
        }
    }

    public static void main(String[] args) {
        Random rand = new Random();
        int N = 10000, P = 12, L = 5;
        int[] A = new int[N],
            B = new int[N],
            C = new int[N];
        String separator = "-----";

        System.out.println(separator);
        System.out.println("Initializing values!");
        for (int i = 0; i < N; ++i) {
            A[i] = rand.nextInt(L);
            B[i] = rand.nextInt(L);
        }
        System.out.println("A: " + Arrays.toString(A));
        System.out.println("B: " + Arrays.toString(B));
        System.out.println(separator);

        cleanUp(C, N);
        System.out.println("Running sequentially!");
        double timeSequentially = measureTimeInMs(() -> runSequentially(A, B, C, N));
        System.out.println("Ran sequentially in " + timeSequentially + "ms!");
        System.out.println("C: " + Arrays.toString(C));
        System.out.println(separator);

        cleanUp(C, N);
        System.out.println("Running in batches!");
        double timeInBatches = measureTimeInMs(() -> runInBatches(A, B, C, N, P));
        System.out.println("Ran in batches in " + timeInBatches + "ms!");
        System.out.println("C: " + Arrays.toString(C));
        System.out.println(separator);

        cleanUp(C, N);
        System.out.println("Running cyclic!");
        double timeCyclic = measureTimeInMs(() -> runCyclic(A, B, C, N, P));
        System.out.println("Ran cyclic in " + timeCyclic + "ms!");
        System.out.println("C: " + Arrays.toString(C));
        System.out.println(separator);
    }
}
