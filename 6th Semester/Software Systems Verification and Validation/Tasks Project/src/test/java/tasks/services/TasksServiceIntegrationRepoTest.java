package tasks.services;

import javafx.collections.ObservableList;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.Mockito;
import tasks.model.ArrayTaskList;
import tasks.model.Task;

import java.util.Date;

import static org.junit.jupiter.api.Assertions.*;

class TasksServiceIntegrationRepoTest {
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
        Task task1 = getMockTask("Task 1", new Date());
        Task task2 = getMockTask("Task 2", new Date());

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
        Task task1 = this.getMockActiveTask("Task 1", now, new Date(now.getTime() + 3600 * 1000), 60);
        Task task2 = this.getMockActiveTask("Task 2", now, new Date(now.getTime() + 3600 * 2 * 1000), 60);

        tasks.add(task1);
        tasks.add(task2);

        Date start = new Date(now.getTime() - 100000);  // 100 secunde
        Date end = new Date(now.getTime() + 100000);    // 100 secunde
        Mockito.when(task1.nextTimeAfter(start)).thenReturn(end);
        Mockito.when(task2.nextTimeAfter(start)).thenReturn(end);

        Iterable<Task> filteredTasks = service.filterTasks(start, end);

        assertNotNull(filteredTasks);
        assertTrue(filteredTasks.iterator().hasNext());
        assertEquals(task1, filteredTasks.iterator().next());
    }

    private Task getMockTask(String title, Date time) {
        Task task = Mockito.mock(Task.class);

        Mockito.when(task.getTitle()).thenReturn(title);
        Mockito.when(task.getTime()).thenReturn(time);

        return task;
    }

    private Task getMockActiveTask(String title, Date start, Date end, int interval) {
        Task task = Mockito.mock(Task.class);

        Mockito.when(task.getTitle()).thenReturn(title);
        Mockito.when(task.getTime()).thenReturn(start);
        Mockito.when(task.getStartTime()).thenReturn(start);
        Mockito.when(task.getEndTime()).thenReturn(end);
        Mockito.when(task.getRepeatInterval()).thenReturn(interval);
        Mockito.when(task.isActive()).thenReturn(true);

        return task;
    }
}