package specific;

import common.Consumer;
import common.MyBlockingQueue;

import java.time.LocalDateTime;
import java.util.List;

public class Solver extends Consumer<Request> {
    final Hall[] halls;
    final List<Request> register;

    public Solver(int id, MyBlockingQueue<Request> queue, Hall[] halls, List<Request> register) {
        super(id, queue);
        this.halls = halls;
        this.register = register;
    }

    @Override
    protected void work() throws Exception {
        while (true) {
            Request req = queue.take();
            if (req == null) {
                System.out.println("[Solver]: Finished!");
                break;
            }
            if (!req.getStatus().equals("in asteptare")) {
                continue;
            }
            synchronized (register) {
                var hall = halls[req.getHallId()];
                if (hall.getOccupied() < hall.getCapacity()) {
                    hall.setOccupied(hall.getOccupied() + 1);
                    req.setStatus("in sala");
                    req.setEnterTime(LocalDateTime.now());
                    Thread.sleep(100);
                    continue;
                }
            }
            queue.put(req);
            Thread.sleep(100);
        }
    }
}
