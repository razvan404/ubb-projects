package domain;

import utils.Utils;

public class ComplexNumber {
    final private double Re;
    final private double Im;

    public ComplexNumber(double Re, double Im) {
        this.Re = Re;
        this.Im = Im;
    }

    public double getRealPart() {
        return Re;
    }

    public double getImaginaryPart() {
        return Im;
    }

    public ComplexNumber add(ComplexNumber oth) {
        double newRe = Re + oth.getRealPart();
        double newIm = Im + oth.getImaginaryPart();
        return new ComplexNumber(newRe, newIm);
    }

    public ComplexNumber subtract(ComplexNumber oth) {
        double newRe = Re - oth.getRealPart();
        double newIm = Im - oth.getImaginaryPart();
        return new ComplexNumber(newRe, newIm);
    }

    public ComplexNumber multiply(ComplexNumber oth) {
        double newRe = Re * oth.getRealPart() - Im * oth.getImaginaryPart();
        double newIm = Re * oth.getImaginaryPart() + Im * oth.getRealPart();
        return new ComplexNumber(newRe, newIm);
    }

    public ComplexNumber divide(ComplexNumber oth) throws ArithmeticException {
        if (oth.getRealPart() == 0 && oth.getImaginaryPart() == 0) {
            throw new ArithmeticException("Invalid operation! Can't divide by 0.");
        }
        double newRe = (Re * oth.getRealPart() + Im * oth.getImaginaryPart())
                / (Math.pow(oth.getRealPart(), 2) + Math.pow(oth.getImaginaryPart(), 2));
        double newIm = (Im * oth.getRealPart() - Re * oth.getImaginaryPart())
                / (Math.pow(oth.getRealPart(), 2) + Math.pow(oth.getImaginaryPart(), 2));
        return new ComplexNumber(newRe, newIm);
    }

    @Override
    public String toString() {
        if (Utils.compareDouble(Im, 1)) {
            return Utils.round(Re, 4) + "+i";
        }
        else if (Utils.compareDouble(Im, -1)) {
            return Utils.round(Re, 4) + "-i";
        }
        else if (Im > 0) {
            return Utils.round(Re, 4) + "+" + Utils.round(Im, 4) + "*i";
        }
        else {
            return Utils.round(Re, 4) + "" + Utils.round(Im, 4) + "*i";
        }
    }
}
