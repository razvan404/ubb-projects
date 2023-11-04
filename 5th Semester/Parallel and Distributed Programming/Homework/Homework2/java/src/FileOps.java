import java.io.*;
import java.util.Random;
import java.util.Scanner;

public class FileOps {
    private static final int ELEMS_LIMIT = 100;
    private static final int CONV_LIMIT = 2;
    public static void generateInput(int n, int m, int k, String filename) throws IOException {
        String filePath = Constants.INPUTS_DIR + filename;
        try (PrintWriter printWriter = new PrintWriter(new FileWriter(filePath))) {
            printWriter.println(n + " " + m);
            Random random = new Random();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m - 1; ++j) {
                    printWriter.print((random.nextInt(ELEMS_LIMIT)) + " ");
                }
                printWriter.println(random.nextInt(ELEMS_LIMIT));
            }
            printWriter.println(k);
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k - 1; ++j) {
                    printWriter.print(random.nextInt(CONV_LIMIT) + " ");
                }
                printWriter.println(random.nextInt(CONV_LIMIT));
            }
        }
    }

    public static int[][][] readFromFile(String filename) throws IOException {
        String filePath = Constants.INPUTS_DIR + filename;
        int[][][] matrices = new int[2][][];
        try (Scanner scanner = new Scanner((new FileReader(filePath)))) {
            String nmLine = scanner.nextLine();
            String[] firstLineSplit = nmLine.split(" ");
            int n = Integer.parseInt(firstLineSplit[0]);
            int m = Integer.parseInt(firstLineSplit[1]);
            matrices[0] = new int[n][m];
            for (int i = 0; i < n; i++) {
                String line = scanner.nextLine();
                String[] lineSplit = line.split(" ");
                for (int j = 0; j < m; j++) {
                    matrices[0][i][j] = Integer.parseInt(lineSplit[j]);
                }
            }
            String kLine = scanner.nextLine();
            int k = Integer.parseInt(kLine);
            matrices[1] = new int[k][k];
            for (int i = 0; i < k; i++) {
                String line = scanner.nextLine();
                String[] lineSplit = line.split(" ");
                for (int j = 0; j < k; j++) {
                    matrices[1][i][j] = Integer.parseInt(lineSplit[j]);
                }
            }
            return matrices;
        }
    }

    public static void writeAnswerToFile(int[][] answer, String filename) throws IOException {
        String filePath = Constants.OUTPUT_DIR + filename;
        try (PrintWriter printWriter = new PrintWriter(new FileWriter(filePath))) {
            int n = answer.length, m = answer[0].length;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m - 1; ++j) {
                    printWriter.print(answer[i][j] + " ");
                }
                printWriter.println(answer[i][m - 1]);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        for (int[] testCase : Constants.TEST_CASES) {
            int n = testCase[0], m = testCase[1], k = testCase[2];
            if (k % 2 != 1) {
                System.out.println("K must be odd");
                System.exit(1);
            }
            generateInput(n, m, k, "input" + n + "_" + m + "_" + k + ".txt");
        }
    }
}