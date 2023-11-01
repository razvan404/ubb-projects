public class Constants {
    public static String HOME_DIR = "../../../"; // to be modified in ../../../ when ran from command line
    public static String FILES_DIR = HOME_DIR + "files/";
    public static String INPUTS_DIR = FILES_DIR + "inputs/";
    public static String OUTPUT_DIR = FILES_DIR + "outputs/";
    public static int[][] TEST_CASES = new int[][] {{10, 10, 3}, {1000, 1000, 5}, {10, 10000, 5}, {10000, 10, 5}};
    public static int[][] THREADS_COUNT = new int[][]{{4}, {2, 4, 8, 16}, {2, 4, 8, 16}, {2, 4, 8, 16}};
    public static String[] FILES_PREFIX = {
        "sequential_",
        "lines_batch_",
        "lines_cyclic_",
        "columns_batch_",
        "columns_cyclic_",
        "linearization_batch_",
        "linearization_cyclic_"
    };
}
