package utils;

import java.math.BigDecimal;
import java.math.RoundingMode;

public class Utils {
    public static boolean compareDouble(double n1, double n2) {
        var tolerance = 0.000000001;
        return Math.abs(n1 - n2) < tolerance;
    }
    public static double round(double value, int places) throws IllegalArgumentException {
        if (places < 0) throw new IllegalArgumentException();

        BigDecimal bd = BigDecimal.valueOf(value);
        bd = bd.setScale(places, RoundingMode.HALF_UP);
        return bd.doubleValue();
    }
}
