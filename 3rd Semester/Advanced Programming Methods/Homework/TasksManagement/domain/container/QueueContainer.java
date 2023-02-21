package domain.container;

import domain.container.BasicContainer;
import domain.task.Task;

public class QueueContainer extends BasicContainer {
    @Override
    public Task remove() {
        if (!isEmpty()) {
            Task toRemove = v[0];
            for (int i = 0; i < size - 1; ++i) {
                v[i] = v[i + 1];
            }
            --size;
            return toRemove;
        }
        return null;
    }
}
