package specific;

import java.time.LocalDateTime;

public class Request {
    private int userId;
    private int hallId;
    private String status;
    private LocalDateTime enterTime;

    public Request(int userId, int hallId) {
        this.userId = userId;
        this.hallId = hallId;
        status = "in asteptare";
        enterTime = null;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public int getHallId() {
        return hallId;
    }

    public void setHallId(int hallId) {
        this.hallId = hallId;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public LocalDateTime getEnterTime() {
        return enterTime;
    }

    public void setEnterTime(LocalDateTime enterTime) {
        this.enterTime = enterTime;
    }

    @Override
    public String toString() {
        return "Request{" +
                "userId=" + userId +
                ", hallId=" + hallId +
                ", status='" + status + '\'' +
                ", enterTime=" + enterTime +
                '}';
    }
}
