package domain.sorter;

public class BubbleSorter implements AbstractSorter {
    private static BubbleSorter sorter = null;
    private BubbleSorter() {}
    public static BubbleSorter getInstance() {
        if (sorter == null) {
            sorter = new BubbleSorter();
        }
        return sorter;
    }
    @Override
    public void sort(int[] v) {
        boolean sorted = false;
        for (int i = 0; i < v.length - 1 && !sorted; ++i) {
            sorted = true;
            for (int j = 0; j < v.length - i - 1; ++j) {
                if (v[j] > v[j + 1]) {
                    int temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                    sorted = false;
                }
            }
        }
    }
}
