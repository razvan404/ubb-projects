package domain.container;

import domain.sorter.AbstractSorter;
import domain.task.Task;
import utils.Constants;

public abstract class BasicContainer implements Container {
    protected Task[] v;
    protected int size;


    public BasicContainer() {
        v = new Task[Constants.INITIAL_CONTAINER_SIZE];
        size = 0;
    }

    private void resize() {
        Task[] v1 = new Task[v.length * Constants.CONTAINER_SIZE_MULTIPLIER];
        System.arraycopy(v, 0, v1, 0, v.length);
        v = v1;
    }


    @Override
    public void add(Task task) {
        if (v.length == size) {
            resize();
        }
        v[size] = task;
        ++size;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }
}
