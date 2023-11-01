import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        if (args.length < 2 || args.length > 4) {
            System.out.println("Usage: java Main <input_filename> <{sequential/lines/columns/linearization}> <{batch/cyclic}> <threadsCount>");
            System.exit(1);
        }
        try {
            String outputFilename;
            String filename = args[0];
            int[][][] matrices = FileOps.readFromFile(filename);
            int n = matrices[0].length, m = matrices[0][0].length, k = matrices[1].length;
            String method = args[1];
            Convolution conv;
            if (method.equals("sequential")) {
                conv = new SequentialConvolution(matrices[0], matrices[1]);
                outputFilename = "sequential_" + n + "_" + m + "_" + k + ".txt";
            } else if (method.equals("block")) {
                int threadsCount = Integer.parseInt(args[2]);
                conv = new BlockConvolution(matrices[0], matrices[1], threadsCount);
                outputFilename = "block_" + n + "_" + m + "_" + k + "_" + threadsCount + ".txt";
            } else {
                String parallelismMethod = args[2];
                int threadsCount = Integer.parseInt(args[3]);
                switch (method) {
                    case "lines" -> {
                        if (parallelismMethod.equals("batch")) {
                            conv = new LinesBatchConvolution(matrices[0], matrices[1], threadsCount);
                        } else {
                            conv = new LinesCyclicConvolution(matrices[0], matrices[1], threadsCount);
                        }
                    }
                    case "columns" -> {
                        if (parallelismMethod.equals("batch")) {
                            conv = new ColumnsBatchConvolution(matrices[0], matrices[1], threadsCount);
                        } else {
                            conv = new ColumnsCyclicConvolution(matrices[0], matrices[1], threadsCount);
                        }
                    }
                    case "linearization" -> {
                        if (parallelismMethod.equals("batch")) {
                            conv = new LinearizationBatchConvolution(matrices[0], matrices[1], threadsCount);
                        } else {
                            conv = new LinearizationCyclicConvolution(matrices[0], matrices[1], threadsCount);
                        }
                    }
                    default -> throw new IllegalArgumentException("Unknown method: " + method);
                }
                outputFilename = method + "_" + parallelismMethod + "_" + n + "_" + m + "_" + k + "_" + threadsCount + ".txt";
            }
            double start = System.nanoTime();
            int[][] answer = conv.apply();
            double end = System.nanoTime();
            FileOps.writeAnswerToFile(answer, outputFilename);
            System.out.println((end - start) * 1e-6);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}