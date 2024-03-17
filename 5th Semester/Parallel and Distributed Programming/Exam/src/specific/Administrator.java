package specific;

import common.MyRunnable;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.List;

public class Administrator extends MyRunnable {
    int delayTime = 200, Dt;
    final List<Request> register;
    Hall[] halls;

    public Administrator(Hall[] halls, List<Request> register, int Dt) {
        this.register = register;
        this.Dt = Dt;
        this.halls = halls;
    }

    @Override
    protected void work() throws Exception {
        LocalDateTime started = LocalDateTime.now();
        while (true) {
            LocalDateTime current = LocalDateTime.now();
            if (!Programmer.programFinished) {
                if (ChronoUnit.MILLIS.between(started, current) > Dt) {
                    Programmer.programFinished = true;
                    synchronized (register) {
                        for (var req : register) {
                            if (req.getStatus().equals("in asteptare")) {
                                req.setStatus("sters");
                            }
                        }
                    }
                }
            }
            synchronized (register) {
                int notFinishedCount = 0;
                for (var req : register) {
                    if (req.getStatus().equals("in sala")) {
                        notFinishedCount += 1;
                        var hall = halls[req.getHallId()];
                        if (ChronoUnit.MILLIS.between(req.getEnterTime(), current) > hall.getMaxTime()) {
                            req.setStatus("finalizat");
                            hall.setOccupied(hall.getOccupied() - 1);
                        }
                    }
                }
                if (notFinishedCount == 0) {
                    break;
                }
                System.out.println("[Administrator]: Not finished at this time: " + notFinishedCount);
            }
            Thread.sleep(delayTime);
        }
    }

    @Override
    protected void finished() {}
}
