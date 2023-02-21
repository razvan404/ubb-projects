package domain.sorter;

public class MergeSorter implements AbstractSorter {
    private static MergeSorter sorter = null;
    private MergeSorter() {}

    public static MergeSorter getInstance() {
        if (sorter == null) {
            sorter = new MergeSorter();
        }
        return sorter;
    }
    private void merge(int[] v, int left, int mid, int right) {
        int len1 = mid - left + 1;
        int len2 = right - mid;

        int[] L = new int[len1];
        int[] R = new int[len2];

        System.arraycopy(v, left, L, 0, len1);
        System.arraycopy(v, mid + 1, R, 0, len2);

        int i = 0, j = 0, k = left;
        while (i < len1 && j < len2) {
            if (L[i] <= R[j]) {
                v[k] = L[i];
                ++i;
            }
            else {
                v[k] = R[j];
                ++j;
            }
            ++k;
        }
        while (i < len1) {
            v[k] = L[i];
            ++i;
            ++k;
        }
        while (j < len2) {
            v[k] = R[j];
            ++j;
            ++k;
        }
    }

    private void mergeSort(int[] v, int left, int right) {
        if (left < right) {
            int mid = left + (right - 1) / 2;
            mergeSort(v, left, mid);
            mergeSort(v, mid + 1, right);
            merge(v, left, mid, right);
        }
    }
    @Override
    public void sort(int[] v) {
        mergeSort(v, 0, v.length - 1);
    }
}
