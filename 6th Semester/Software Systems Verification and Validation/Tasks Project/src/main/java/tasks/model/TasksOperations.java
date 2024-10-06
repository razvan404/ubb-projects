package tasks.model;

import javafx.collections.ObservableList;

import java.util.*;

public class TasksOperations
{
    private final ArrayList<Task> tasks;

    public TasksOperations(ObservableList<Task> tasksList)
    {
        tasks = new ArrayList<>();
        tasks.addAll(tasksList);
    }

    public Iterable<Task> incoming(Date start, Date end)
    {
        ArrayList<Task> incomingTasks = new ArrayList<>();
        if (!end.before(start)) {
            for (Task task : tasks) {
                Date nextTime = task.nextTimeAfter(start);
                if (nextTime != null) {
                    if ((nextTime.before(end) || nextTime.equals(end))) {
                        incomingTasks.add(task);
                        System.out.println(task.getTitle());
                    }
                }
            }
        }

        return incomingTasks;
    }

    public SortedMap<Date, Set<Task>> calendar(Date start, Date end)
    {
        Iterable<Task> incomingTasks = this.incoming(start, end);
        TreeMap<Date, Set<Task>> calendar = new TreeMap<>();

        for (Task incomingTask : incomingTasks)
        {
            Date nextTimeAfter = incomingTask.nextTimeAfter(start);
            while (nextTimeAfter!= null && (nextTimeAfter.before(end) || nextTimeAfter.equals(end)))
            {
                if (calendar.containsKey(nextTimeAfter))
                {
                    calendar.get(nextTimeAfter).add(incomingTask);
                }
                else
                {
                    HashSet<Task> oneDateTasks = new HashSet<>();
                    oneDateTasks.add(incomingTask);
                    calendar.put(nextTimeAfter, oneDateTasks);
                }
                nextTimeAfter = incomingTask.nextTimeAfter(nextTimeAfter);
            }
        }

        return calendar;
    }

    public List<Task> getTasks() {
        return tasks;
    }
}