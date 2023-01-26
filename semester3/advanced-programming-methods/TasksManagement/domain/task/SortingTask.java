package domain.task;

import domain.sorter.*;

import java.util.Arrays;

public class SortingTask extends Task {
    private final int[] v;
    private AbstractSorter sorter;

    public SortingTask(String taskID, String descriere, int[] v, SorterStrategy strategy) {
        super(taskID, descriere);
        this.v = v;
        if (strategy == SorterStrategy.BubbleSort) {
            sorter = BubbleSorter.getInstance();
        }
        else if (strategy == SorterStrategy.QuickSort) {
            sorter = QuickSorter.getInstance();
        }
        else if (strategy == SorterStrategy.MergeSort) {
            sorter = MergeSorter.getInstance();
        }
    }

    @Override
    public String toString() {
        return super.toString() + " | sorted array=" + Arrays.toString(v);
    }

    @Override
    public void execute() {
        sorter.sort(v);
        System.out.println(this);
    }
}
