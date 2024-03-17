package specific;

public class Hall {
    private int hallId, capacity, occupied, maxTime;

    public Hall(int hallId, int capacity, int occupied, int maxTime) {
        this.hallId = hallId;
        this.capacity = capacity;
        this.occupied = occupied;
        this.maxTime = maxTime;
    }

    public int getHallId() {
        return hallId;
    }

    public void setHallId(int hallId) {
        this.hallId = hallId;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public int getOccupied() {
        return occupied;
    }

    public void setOccupied(int occupied) {
        this.occupied = occupied;
    }

    public int getMaxTime() {
        return maxTime;
    }

    public void setMaxTime(int maxTime) {
        this.maxTime = maxTime;
    }

    @Override
    public String toString() {
        return "Hall{" +
                "hallId=" + hallId +
                ", capacity=" + capacity +
                ", occupied=" + occupied +
                ", maxTime=" + maxTime +
                '}';
    }
}
