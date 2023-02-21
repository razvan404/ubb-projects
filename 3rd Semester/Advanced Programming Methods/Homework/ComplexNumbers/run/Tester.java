package run;

import domain.ComplexNumber;
import domain.Operation;
import expression.AdditionExpression;
import expression.DivisionExpression;
import expression.MultiplicationExpression;
import expression.SubstractionExpression;
import utils.Utils;
public class Tester {
    private static void testComplexNumber() {
        ComplexNumber n1 = new ComplexNumber(3, 7);
        assert n1.getRealPart() == 3;
        assert n1.getImaginaryPart() == 7;

        ComplexNumber n2 = new ComplexNumber(-3.2, -5.7);
        assert n2.getRealPart() == -3.2;
        assert n2.getImaginaryPart() == -5.7;


        ComplexNumber one = new ComplexNumber(1, 0);
        ComplexNumber i = new ComplexNumber(0, 1);
        ComplexNumber zero = new ComplexNumber(0, 0);

        ComplexNumber add = n1.add(n2);
        assert Utils.compareDouble(add.getRealPart(), -0.2);
        assert Utils.compareDouble(add.getImaginaryPart(), 1.3);

        ComplexNumber subtract = n1.subtract(n2);
        assert Utils.compareDouble(subtract.getRealPart(), 6.2);
        assert Utils.compareDouble(subtract.getImaginaryPart(), 12.7);

        ComplexNumber multiply = n1.multiply(n2);
        assert Utils.compareDouble(multiply.getRealPart(), 30.3);
        assert Utils.compareDouble(multiply.getImaginaryPart(), -39.5);

        ComplexNumber divideByi = n1.divide(i);
        assert Utils.compareDouble(divideByi.getRealPart(), 7);
        assert Utils.compareDouble(divideByi.getImaginaryPart(), -3);

        ComplexNumber divideBy1 = n1.divide(one);
        assert Utils.compareDouble(divideBy1.getRealPart(), 3);
        assert Utils.compareDouble(divideBy1.getImaginaryPart(), 7);

        try {
            ComplexNumber divideBy0 = n1.divide(zero);
        }
        catch (Exception e) {
            assert e.getMessage().equals("Invalid operation! Can't divide by 0.");
        }

        assert divideBy1.toString().equals("3.0+7.0*i");
        assert multiply.toString().equals("30.3-39.5*i");
    }

    private static void testComplexExpression() {
        ComplexNumber n1 = new ComplexNumber(3, 7);
        ComplexNumber n2 = new ComplexNumber(-3.2, -5.7);
        ComplexNumber one = new ComplexNumber(1, 0);
        ComplexNumber i = new ComplexNumber(0, 1);
        ComplexNumber zero = new ComplexNumber(0, 0);

        ComplexNumber[] numbers = { n1, n2, one, i };

        AdditionExpression add = new AdditionExpression(Operation.ADDITION, numbers);
        ComplexNumber addResult = add.execute();
        assert Utils.compareDouble(addResult.getRealPart(), 0.8);
        assert Utils.compareDouble(addResult.getImaginaryPart(), 2.3);

        SubstractionExpression sub = new SubstractionExpression(Operation.SUBSTRACTION, numbers);
        ComplexNumber subResult = sub.execute();
        assert Utils.compareDouble(subResult.getRealPart(), 5.2);
        assert Utils.compareDouble(subResult.getImaginaryPart(), 11.7);

        MultiplicationExpression mul = new MultiplicationExpression(Operation.MULTIPLICATION, numbers);
        ComplexNumber mulResult = mul.execute();
        assert Utils.compareDouble(mulResult.getRealPart(), 39.5);
        assert Utils.compareDouble(mulResult.getImaginaryPart(), 30.3);

        DivisionExpression div = new DivisionExpression(Operation.DIVISION, numbers);
        ComplexNumber divResult = div.execute();
        assert Utils.compareDouble(divResult.getRealPart(), -0.12403463608705828);
        assert Utils.compareDouble(divResult.getImaginaryPart(), 1.1584366955300724);

        try {
            ComplexNumber[] numbersWithZero = { n1, n2, one, i, zero };
            DivisionExpression divError = new DivisionExpression(Operation.DIVISION, numbersWithZero);
            ComplexNumber divErrorResult = div.execute();
        }
        catch (Exception e) {
            assert e.equals("Invalid operation! Can't divide by 0.");
        }

    }

    public static void run() {
        testComplexNumber();
        testComplexExpression();
    }
}
