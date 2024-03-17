import common.MyBlockingQueue;
import specific.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        int A = 4, B = 3, Dt = 7000;
        Hall[] halls = new Hall[] {
                new Hall(1, 5, 0, 2),
                new Hall(2, 7, 0, 5),
                new Hall(3, 10, 0, 3),
                new Hall(4, 8, 0, 7),
                new Hall(5, 12, 0, 6)
        };
        MyBlockingQueue<Request> queue = new MyBlockingQueue<>(A, B);
        List<Request> register = new ArrayList<>();
        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < A; ++i) {
            var thread = new Thread(new Programmer(i, queue, halls.length, register));
            thread.start();
            threads.add(thread);
        }

        for (int i = 0; i < B; ++i) {
            var thread = new Thread(new Solver(i, queue, halls, register));
            thread.start();
            threads.add(thread);
        }

        var administrator = new Thread(new Administrator(halls, register, Dt));
        administrator.start();
        threads.add(administrator);

        for (var thread : threads) {
            thread.join();
        }
        System.out.println("[Main] Final halls: " + Arrays.toString(halls));
    }
}