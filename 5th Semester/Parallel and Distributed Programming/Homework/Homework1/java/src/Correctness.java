import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;

public class Correctness {
    public static void main(String[] args) throws IOException {
        int testCaseIdx = 0;
        for (int[] testCase : Constants.TEST_CASES) {
            int n = testCase[0], m = testCase[1], k = testCase[2];
            String filename = Constants.FILES_PREFIX[0] + n + "_" + m + "_" + k + ".txt";
            Path path1 = Path.of(Constants.OUTPUT_DIR + filename);
            byte[] file1Content = Files.readAllBytes(path1);
            for (int i = 1; i < Constants.FILES_PREFIX.length; ++i) {
                for (int threadsCount : Constants.THREADS_COUNT[testCaseIdx]) {
                    filename = Constants.FILES_PREFIX[i] + n + "_" + m + "_" + k + "_" + threadsCount + ".txt";
                    Path path2 = Path.of(Constants.OUTPUT_DIR + filename);
                    byte[] file2Content = Files.readAllBytes(path2);
                    if (!Arrays.equals(file1Content, file2Content)) {
                        System.out.println("Files " + path1 + " and " + path2 + " are different");
                        return;
                    }
                }
            }
            testCaseIdx += 1;
        }
        System.out.println("All files are equal");
    }
}
