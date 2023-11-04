import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        if (args.length < 2 || args.length > 3) {
            System.out.println("Usage: java Main <input_filename> <{sequential/lines}> <threadsCount>");
            System.exit(1);
        }
        try {
            String outputFilename;
            String filename = args[0];
            int[][][] matrices = FileOps.readFromFile(filename);
            int n = matrices[0].length, m = matrices[0][0].length, k = matrices[1].length;
            String method = args[1];
            InlineConvolution conv;
            if (method.equals("sequential")) {
                conv = new InlineSequentialConvolution(matrices[0], matrices[1]);
                outputFilename = "sequential_" + n + "_" + m + "_" + k + ".txt";
            } else if (method.equals("lines")) {
                int threadsCount = Integer.parseInt(args[2]);
                conv = new InlineLinesConvolution(matrices[0], matrices[1], threadsCount);
                outputFilename = "lines_" + n + "_" + m + "_" + k + "_" + threadsCount + ".txt";
            } else {
                throw new RuntimeException("Not a valid method.");
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