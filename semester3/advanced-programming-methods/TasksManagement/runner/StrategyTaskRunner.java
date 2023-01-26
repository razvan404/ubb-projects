package runner;

import domain.container.Container;
import domain.container.ContainerStrategy;
import domain.task.Task;
import factory.TaskContainerFactory;

public class StrategyTaskRunner implements TaskRunner {
    private Container container;

    public StrategyTaskRunner(ContainerStrategy strategy) {
        container = TaskContainerFactory.getInstance().createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        if (hasTask()) {
            container.remove().execute();
        }
    }
    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
