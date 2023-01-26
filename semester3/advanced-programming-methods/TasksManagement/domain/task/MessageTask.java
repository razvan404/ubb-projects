package domain.task;

import utils.Constants;

import java.time.LocalDateTime;

public class MessageTask extends Task {
    private final String mesaj;
    private final String from;
    private final String to;
    private final LocalDateTime date;

    public MessageTask(String taskID, String descriere, String mesaj, String from, String to, LocalDateTime date) {
        super(taskID, descriere);
        this.mesaj = mesaj;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public String toString() {
        return super.toString() + " | message=" + '"' + mesaj + '"'
                + " | from=" + from
                + " | to=" + to
                + " | date=" + date.format(Constants.DATE_TIME_FORMATTER);
    }

    @Override
    public void execute() {
        System.out.println(this);
    }
}
