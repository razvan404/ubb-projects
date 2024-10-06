package tasks.model;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import java.util.Locale;

import static org.junit.jupiter.api.Assertions.*;

class TaskTest {

    private Task task;

    @BeforeEach
    void setUp() {
        try {
            task=new Task("new task",Task.getDateFormat().parse("2023-02-12 10:10"));
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    @Test
    public void testTaskCreation() throws ParseException {
       assert task.getTitle() == "new task";
       assert task.getFormattedDateStart().equals(task.getDateFormat().format(Task.getDateFormat().parse("2023-02-12 10:10")));
    }

    @Test
    public void getTime()
    {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm");
        assertEquals("2023-02-12 10:10", sdf.format(task.getTime()));
        String dateString = "January 2, 2010";
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy", Locale.ENGLISH);
        LocalDate localDate = LocalDate.parse(dateString, formatter);
        task.setTime(Date.from(localDate.atStartOfDay(ZoneId.systemDefault()).toInstant()));
        assertEquals("2010-01-02 00:00", sdf.format(task.getTime()));
    }

    @AfterEach
    void tearDown() {
    }
}