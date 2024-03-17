package common;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MyBlockingQueue<T> {
    private int producersCount;
    private int consumersCount;
    private final Object consumersFinishedLock = new Object();

    private final Integer capacity;
    private final Queue<T> elems;

    private final Lock lock = new ReentrantLock();
    private final Condition notFull = lock.newCondition();
    private final Condition notEmpty = lock.newCondition();

    public MyBlockingQueue(int producersCount, int consumersCount, int capacity) {
        this.producersCount = producersCount;
        this.consumersCount = consumersCount;
        this.capacity = capacity;
        elems = new LinkedList<>();
    }

    public MyBlockingQueue(int producersCount, int consumersCount) {
        this.producersCount = producersCount;
        this.consumersCount = consumersCount;
        capacity = null;
        elems = new LinkedList<>();
    }

    public void put(T elem) throws InterruptedException {
        lock.lock();
        if (capacity != null && elems.size() == capacity) {
            notFull.await();
        }
        elems.add(elem);
        notEmpty.signal();
        lock.unlock();
    }

    public T take() throws InterruptedException {
        lock.lock();
        while (elems.isEmpty() && producersCount > 0) {
            notEmpty.await();
        }
        T elem = elems.poll();
        notFull.signal();
        lock.unlock();
        return elem;
    }

    public void stopProducer() {
        lock.lock();
        producersCount--;
        if (producersCount == 0) {
            notEmpty.signalAll();
        }
        lock.unlock();
    }

    public void stopConsumer() {
        lock.lock();
        consumersCount--;
        if (consumersCount == 0) {
            synchronized (consumersFinishedLock) {
                consumersFinishedLock.notifyAll();
            }
        }
        lock.unlock();
    }

    public boolean finished() {
        return producersCount == 0;
    }

    public int size() {
        return elems.size();
    }

    public void awaitTermination() throws InterruptedException {
        synchronized (consumersFinishedLock) {
            if (!finished()) {
                consumersFinishedLock.wait();
            }
        }
    }
}
