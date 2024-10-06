package tasks.model;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;

import java.text.ParseException;
import java.util.Arrays;
import java.util.Date;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

class ArrayTaskListTest {

    @Mock
    private ArrayTaskList tasks;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    public void add() throws ParseException {
        Task task = getMockTask("new task",Task.getDateFormat().parse("2023-02-12 10:10"));
        Task task2 = getMockTask("new task2",Task.getDateFormat().parse("2023-02-12 10:10"));
        Mockito.when(tasks.getAll()).thenReturn(Arrays.asList(task));
        Mockito.doNothing().when(tasks).add(task2);

        this.tasks.add(task2);

        Mockito.verify(tasks, times(1)).add(task2);
        Mockito.verify(tasks, never()).getAll();

        assert this.tasks.getAll().size() == 1;

        Mockito.verify(tasks, times(1)).getAll();
        assertEquals("new task", tasks.getAll().get(0).getTitle());
    }

    @Test
    void remove() throws ParseException {
        Task task1 = getMockTask("new task", Task.getDateFormat().parse("2023-02-12 10:10"));
        Task task2 = getMockTask("new task2", Task.getDateFormat().parse("2023-02-12 10:10"));

        Mockito.when(tasks.getAll()).thenReturn(Arrays.asList(task1, task2));
        Mockito.when(tasks.remove(task1)).thenReturn(true);

        boolean result = tasks.remove(task1);
        assert result;

        Mockito.verify(tasks, times(1)).remove(task1);
        Mockito.verify(tasks, never()).getAll();
        Mockito.verifyNoMoreInteractions(tasks);

        Mockito.when(tasks.getAll()).thenReturn(Arrays.asList(task2));
        assert tasks.getAll().size() == 1;
        assertEquals("new task2", tasks.getAll().get(0).getTitle());
    }

    @AfterEach
    void tearDown() {
    }

    private Task getMockTask(String title, Date time) {
        Task task = Mockito.mock(Task.class);

        Mockito.when(task.getTitle()).thenReturn(title);
        Mockito.when(task.getTime()).thenReturn(time);

        return task;
    }
}