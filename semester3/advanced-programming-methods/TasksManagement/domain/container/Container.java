package domain.container;

import domain.task.Task;

public interface Container {
    Task remove();
    void add (Task task);
    int size();
    boolean isEmpty();
}

