package run;

import domain.container.ContainerStrategy;
import domain.sorter.SorterStrategy;
import domain.task.MessageTask;
import domain.task.SortingTask;
import domain.task.Task;
import runner.*;

import java.time.LocalDateTime;

public class Tester {
    static private void testSorter() {
        Task bs = new SortingTask("0", "bubble sorting", new int[]{5, 3, 4, 1, 2}, SorterStrategy.BubbleSort);
        Task qs = new SortingTask("1", "quick sorting", new int[]{5, 3, 4, 1, 2}, SorterStrategy.QuickSort);
        Task ms = new SortingTask("1", "merge sorting", new int[]{5, 3, 4, 1, 2}, SorterStrategy.QuickSort);

        System.out.println("\n\tSorting Tasks: ");
        bs.execute();
        qs.execute();
        ms.execute();
    }
    static private Task[] getMessages() {
        Task m1 = new MessageTask("1", "Feedback MAP-LAB1",
                "Ai obtinut 9.60", "Gigi", "Ana", LocalDateTime.of(2022, 10, 8, 20, 51));
        Task m2 = new MessageTask("2", "Feedback MAP-LAB1",
                "Ai obtinut 5.40", "Gigi", "Costin", LocalDateTime.of(2022, 10, 8, 20, 55));
        Task m3 = new MessageTask("3", "Feedback PLF-LAB2",
                "Ai obtinut 7.70", "Grigore", "Leonard", LocalDateTime.of(2022, 11, 10, 16, 34));
        Task m4 = new MessageTask("4", "Feedback PLF-LAB2",
                "Ai obtinut 8.80", "Grigore", "Cristian", LocalDateTime.of(2022, 11, 10, 16, 42));
        Task m5 = new MessageTask("5", "Feedback BD-LAB3",
                "Ai obtinut 6.90", "Mircea", "Mirela", LocalDateTime.of(2022, 12, 13, 8, 22));
        return new Task[]{m1, m2, m3, m4, m5};
    }

    static public void run(String[] args) {
        testSorter();
        if (args.length == 1) {
            TaskRunner strategyRunner, delayStrategyRunner, printerStrategyRunner;
            if (args[0].equals("LIFO")) {
                strategyRunner = new StrategyTaskRunner(ContainerStrategy.LIFO);
                delayStrategyRunner = new StrategyTaskRunner(ContainerStrategy.LIFO);
                printerStrategyRunner = new StrategyTaskRunner(ContainerStrategy.LIFO);
            }
            else if (args[0].equals("FIFO")) {
                strategyRunner = new StrategyTaskRunner(ContainerStrategy.FIFO);
                delayStrategyRunner = new StrategyTaskRunner(ContainerStrategy.FIFO);
                printerStrategyRunner = new StrategyTaskRunner(ContainerStrategy.FIFO);
            }
            else {
                return;
            }

            TaskRunner delayRunner = new DelayTaskRunner(delayStrategyRunner);
            TaskRunner printerRunner = new PrinterTaskRunner(printerStrategyRunner);

            for (Task t : getMessages()) {
                strategyRunner.addTask(t);
                delayRunner.addTask(t);
                printerRunner.addTask(t);
            }

            System.out.println("\n\tStrategy Runner:");
            strategyRunner.executeAll();
            System.out.println("\n\tDelay Runner:");
            delayRunner.executeAll();
            System.out.println("\n\tPrinter Runner:");
            printerRunner.executeAll();
        }
    }
}
