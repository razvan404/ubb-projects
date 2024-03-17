package specific;

import common.MyBlockingQueue;
import common.Producer;
import common.RNG;

import java.time.LocalDateTime;
import java.util.List;

public class Programmer extends Producer<Request> {
    int hallsCount;
    final List<Request> register;
    public static boolean programFinished = false;

    public Programmer(int id, MyBlockingQueue<Request> queue, int hallsCount, List<Request> register) {
        super(id, queue);
        this.hallsCount = hallsCount;
        this.register = register;
    }

    @Override
    protected void work() throws Exception {
        int iter = 0;
        while (true) {
            if (programFinished) {
                System.out.println("[Programmer]: Time to head out!");
                break;
            }
            Request req = new Request(id * 100000 + iter, RNG.between(0, hallsCount - 1));
            this.queue.put(req);
            synchronized (register) {
                register.add(req);
            }
            iter++;
            Thread.sleep(RNG.between(170, 200));
        }
    }
}
