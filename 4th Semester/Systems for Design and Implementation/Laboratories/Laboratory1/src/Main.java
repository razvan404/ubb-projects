import java.util.Random;

public class Main {
    public static void main(String[] args) {
        switch (new Random().nextInt(0, 5)) {
            case 0 -> System.out.println("Hello world!");
            case 1 -> System.out.println("World hello!");
            case 2 -> System.out.println("Hello hello!");
            case 3 -> System.out.println("World world!");
            case 4 -> System.out.println("Hello!");
        }
    }
}