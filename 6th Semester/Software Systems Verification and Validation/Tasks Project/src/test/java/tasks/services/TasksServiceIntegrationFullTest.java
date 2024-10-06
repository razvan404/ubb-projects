package tasks.services;

import javafx.collections.ObservableList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import tasks.model.ArrayTaskList;
import tasks.model.Task;

import java.util.Date;

import static org.junit.jupiter.api.Assertions.*;

class TasksServiceIntegrationFullTest {
    @Mock
    private ArrayTaskList tasks;

    @InjectMocks
    private TasksService service;

    @BeforeEach
    public void setUp() {
        tasks = new ArrayTaskList();
        service = new TasksService(tasks);
    }

    @Test
    public void getObservableListTest() {
        Task task1 = new Task("Task 1", new Date());
        Task task2 = new Task("Task 2", new Date());

        tasks.add(task1);
        tasks.add(task2);

        ObservableList<Task> observableList = service.getObservableList();
        assert this.tasks.getAll().size() == 2;

        assertNotNull(observableList);
        assertEquals(2, observableList.size());
        assertTrue(observableList.contains(task1));
        assertTrue(observableList.contains(task2));
    }

    @Test
    void filterTasksTest() {
        // String title, Date start, Date end, int interval
        Date now = new Date();
        Task task1 = new Task("Task 1", now, new Date(now.getTime() + 3600 * 1000), 60);
        task1.setActive(true);
        Task task2 = new Task("Task 2", now, new Date(now.getTime() + 3600 * 2 * 1000), 60);
        task2.setActive(true);

        tasks.add(task1);
        tasks.add(task2);

        Date start = new Date(now.getTime() - 100000);  // 100 secunde
        Date end = new Date(now.getTime() + 100000);    // 100 secunde

        Iterable<Task> filteredTasks = service.filterTasks(start, end);

        assertNotNull(filteredTasks);
        assertTrue(filteredTasks.iterator().hasNext());
        assertEquals(task1, filteredTasks.iterator().next());
    }
}