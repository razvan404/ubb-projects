
public class TestingThreads {
    public static class HelloWorldThread extends Thread {
        private final int index;
        public HelloWorldThread(int index) {
            this.index = index;
        }

        @Override
        public void run() {
            System.out.println("Hello! I'm the thread with the identifier: " + index);
        }
    }

    public static void main(String[] args) {
        int p = 10;
        Thread[] threads = new Thread[p];
        for (int i = 0; i < p; ++i) {
            threads[i] = new HelloWorldThread(i);
            threads[i].start();
        }
        for (int i = 0; i < p; ++i) {
            try {
                threads[i].join();
            } catch (InterruptedException ex) {
                System.err.println(ex.getMessage());
            }
        }
    }
}