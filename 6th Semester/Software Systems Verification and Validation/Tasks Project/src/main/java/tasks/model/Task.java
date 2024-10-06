package tasks.model;

import org.apache.log4j.Logger;
import tasks.services.TaskIO;

import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Task implements Serializable, Cloneable
{
    private String title;
    private Date time;
    private Date start;
    private Date end;
    private int interval;
    private boolean active;

    private static final Logger log = Logger.getLogger(Task.class.getName());
    private static final SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm");

    public static SimpleDateFormat getDateFormat()
    {
        return sdf;
    }

    public Task(String title, Date time) throws IllegalArgumentException
    {
        if (time.getTime() < 0)
        {
            log.error("time below bound");
            throw new IllegalArgumentException("Time cannot be negative");
        }

        this.title = title;
        this.time = time;
        this.start = time;
        this.end = time;
    }

    public Task(String title, Date start, Date end, int interval) throws IllegalArgumentException
    {
        if (start.getTime() < 0 || end.getTime() < 0)
        {
            log.error("time below bound");
            throw new IllegalArgumentException("Time cannot be negative");
        }
        if (interval < 1)
        {
            log.error("interval < than 1");
            throw new IllegalArgumentException("interval should be > 0");
        }

        this.title = title;
        this.start = start;
        this.end = end;
        this.interval = interval;
        this.time = start;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }
    public boolean isActive(){
        return this.active;
    }

    public void setActive(boolean active){
        this.active = active;
    }

    public Date getTime() {
        return time;
    }

    public void setTime(Date time)
    {
        this.time = time;
        this.start = time;
        this.end = time;
        this.interval = 0;
    }

    public Date getStartTime() {
        return start;
    }

    public Date getEndTime() {
        return end;
    }
    public int getRepeatInterval(){
        return Math.max(interval, 0);
    }

    public void setTime(Date start, Date end, int interval)
    {
        this.time = start;
        this.start = start;
        this.end = end;
        this.interval = interval;

    }
    public boolean isRepeated()
    {
        return !(this.interval == 0);
    }

    private boolean isDateValid(Date current) {
        return !(current.equals(end) || current.after(end) || !isActive());
    }

    private Date loopDates(Date current) {
        Date timeBefore = start;
        Date timeAfter = start;
        for (long i = start.getTime(); i <= end.getTime(); i += interval * 1000L) {
            if (current.equals(timeAfter)) {
                return new Date(timeAfter.getTime() + interval * 1000L);
            }

            if (current.after(timeBefore) && current.before(timeAfter)) {
                return timeAfter;
            }

            timeBefore = timeAfter;
            timeAfter = new Date(timeAfter.getTime() + interval * 1000L);
        }
        return null;
    }

    public Date nextTimeAfter(Date current) {
        if (!isDateValid(current)) {
            return null;
        }

        if (isRepeated()) {
            if (current.before(start)) {
                return start;
            }
            return loopDates(current);
        } else if (current.before(time)) {
            return time;
        }

        return null;
    }


    //duplicate methods for TableView which sets column
    // value by single method and doesn't allow passing parameters
    public String getFormattedDateStart()
    {
        return sdf.format(start);
    }

    public String getFormattedDateEnd()
    {
        return sdf.format(end);
    }

    public String getFormattedRepeated()
    {
        if (isRepeated())
        {
            String formattedInterval = TaskIO.getFormattedInterval(interval);
            return "Every " + formattedInterval;
        }

        return "No";
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o)
        {
            return true;
        }

        if (o == null || getClass() != o.getClass())
        {
            return false;
        }

        Task task = (Task)o;

        if (!time.equals(task.time))
        {
            return false;
        }

        if (!start.equals(task.start))
        {
            return false;
        }

        if (!end.equals(task.end))
        {
            return false;
        }

        if (interval != task.interval)
        {
            return false;
        }

        if (active != task.active)
        {
            return false;
        }

        return title.equals(task.title);
    }

    @Override
    public int hashCode()
    {
        int result = title.hashCode();
        result = 31 * result + time.hashCode();
        result = 31 * result + start.hashCode();
        result = 31 * result + end.hashCode();
        result = 31 * result + interval;
        result = 31 * result + (active ? 1 : 0);
        return result;
    }

    @Override
    public String toString()
    {
        return "Task{" +
                "title='" + title + '\'' +
                ", time=" + time +
                ", start=" + start +
                ", end=" + end +
                ", interval=" + interval +
                ", active=" + active +
                '}';
    }

    @Override
    protected Task clone() throws CloneNotSupportedException
    {
        Task task = (Task)super.clone();
        task.time = (Date)this.time.clone();
        task.start = (Date)this.start.clone();
        task.end = (Date)this.end.clone();
        return task;
    }
}