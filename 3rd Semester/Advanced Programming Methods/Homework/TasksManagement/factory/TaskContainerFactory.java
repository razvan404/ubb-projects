package factory;

import domain.container.Container;
import domain.container.ContainerStrategy;
import domain.container.QueueContainer;
import domain.container.StackContainer;

public class TaskContainerFactory implements Factory {
    static TaskContainerFactory factory = null;

    private TaskContainerFactory() {}

    static public TaskContainerFactory getInstance() {
        if (factory == null) {
            factory = new TaskContainerFactory();
        }
        return factory;
    }

    @Override
    public Container createContainer(ContainerStrategy strategy) {
        if (strategy == ContainerStrategy.LIFO) {
            return new StackContainer();
        }
        if (strategy == ContainerStrategy.FIFO) {
            return new QueueContainer();
        }
        return null;
    }
}
