package common;

import java.util.Random;

public class RNG {
    static Random rnd = new Random();

    public static int number() {
        return rnd.nextInt(1000);
    }
    public static int between(int a, int b) {
        return rnd.nextInt(a, b + 1);
    }
}
