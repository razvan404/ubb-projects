package runner;

import utils.Constants;

import java.time.LocalDateTime;

public class PrinterTaskRunner extends AbstractTaskRunner {
    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        taskRunner.executeOneTask();
        System.out.println("Task-ul a fost executat la ora: " + LocalDateTime.now().format(Constants.DATE_TIME_FORMATTER));
    }
}
