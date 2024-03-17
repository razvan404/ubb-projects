package common;

public abstract class MyRunnable implements Runnable {
    @Override
    public void run() {
        try {
            work();
            finished();
        } catch (Exception exc) {
            throw new RuntimeException(exc);
        }
    }

    protected abstract void work() throws Exception;

    protected abstract void finished();
}
