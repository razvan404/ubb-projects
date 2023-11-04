import java.io.IOException;

public class Demo {
    public static void main(String[] args) throws IOException {
        String input = "input10_10_3.txt";
        int[][][] matrices = FileOps.readFromFile(input);
        int n = matrices[0].length, m = matrices[0][0].length, k = matrices[1].length;
        String outputFilename = "demo_classic_" + n + "_" + m + "_" + k + ".txt";
        double start = System.nanoTime();
        Convolution convClassic = new SequentialConvolution(matrices[0], matrices[1]);
        double end = System.nanoTime();
        int[][] answer = convClassic.apply();
        double timeClassic = (end - start) * 1e-6;
        FileOps.writeAnswerToFile(answer, outputFilename);

        InlineConvolution conv = new InlineSequentialConvolution(matrices[0], matrices[1]);
        outputFilename = "demo_inline_" + n + "_" + m + "_" + k + ".txt";
        start = System.nanoTime();
        answer = conv.apply();
        end = System.nanoTime();
        double timeInline = (end - start) * 1e-6;
        FileOps.writeAnswerToFile(answer, outputFilename);

        System.out.println("Time taken:\nClassic: " + timeClassic + "ms\nInline sequential: " + timeInline + "ms");
        for (int i = 1; i <= 3; ++i) {
            int p = 1 << i;
            matrices = FileOps.readFromFile(input);
            conv = new InlineLinesConvolution(matrices[0], matrices[1], p);
            outputFilename = "demo_parallel_" + n + "_" + m + "_" + k + "_" + p + ".txt";
            start = System.nanoTime();
            answer = conv.apply();
            end = System.nanoTime();
            double timeParallel = (end - start) * 1e-6;
            FileOps.writeAnswerToFile(answer, outputFilename);
            System.out.println("Time parallel with " + p + " threads: " + timeParallel);
        }
    }
}
