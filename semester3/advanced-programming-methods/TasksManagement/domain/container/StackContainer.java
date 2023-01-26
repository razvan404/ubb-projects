package domain.container;

import domain.task.Task;

public class StackContainer extends BasicContainer {
    @Override
    public Task remove() {
        if (!isEmpty()) {
            --size;
            return v[size];
        }
        return null;
    }
}
