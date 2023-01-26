package domain.sorter;

public class QuickSorter implements AbstractSorter {
    private static QuickSorter sorter = null;
    private QuickSorter() {}

    public static QuickSorter getInstance() {
        if (sorter == null) {
            sorter = new QuickSorter();
        }
        return sorter;
    }
    private int partition(int[] v, int left, int right) {
        int pivot = v[right];
        int i = left;

        for (int j = left; j < right; ++j) {
            if (v[j] <= pivot) {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
                ++i;
            }
        }
        int temp = v[i];
        v[i] = v[right];
        v[right] = temp;

        return i;
    }

    private void quickSort(int[] v, int left, int right) {
        if (left < right) {
            int p = partition(v, left, right);
            quickSort(v, left, p - 1);
            quickSort(v, p + 1, right);
        }
    }

    @Override
    public void sort(int[] v) {
        quickSort(v, 0, v.length - 1);
    }
}
