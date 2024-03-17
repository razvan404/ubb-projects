package common;

public abstract class Producer<T> extends MyRunnable {
    protected final int id;
    protected final MyBlockingQueue<T> queue;

    public Producer(int id, MyBlockingQueue<T> queue) {
        this.id = id;
        this.queue = queue;
    }

    @Override
    protected void finished() {
        this.queue.stopProducer();
    }
}
