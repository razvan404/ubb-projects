package common;

import java.util.List;

public abstract class MultiProducer<T> extends MyRunnable {
    protected final int id;
    protected final List<MyBlockingQueue<T>> queues;

    public MultiProducer(int id, List<MyBlockingQueue<T>> queues) {
        this.id = id;
        this.queues = queues;
    }

    @Override
    protected void finished() {
        for (var queue : queues) {
            queue.stopProducer();
        }
    }
}
