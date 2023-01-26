package parser;


import domain.ComplexNumber;
import domain.Operation;
import expression.ComplexExpression;
import factory.ExpressionFactory;

public class ExpressionParser {
    private static Operation getOperation(String[] args) throws ArithmeticException {
        for (int i = 1; i < args.length; i += 2) {
            if (!args[i].equals(args[1])) {
                throw new ArithmeticException("Invalid operators!");
            }
        }
        Operation op;
        switch (args[1]) {
            case "+":
                op = Operation.ADDITION;
                break;
            case "-":
                op = Operation.SUBSTRACTION;
                break;
            case "*":
                op = Operation.MULTIPLICATION;
                break;
            case "/":
                op = Operation.DIVISION;
                break;
            default:
                throw new ArithmeticException("Invalid operators!");
        }
        return op;
    }

    private static ComplexNumber complexStringToNumber(String arg) throws NumberFormatException {
        double Re, Im;
        if (arg.charAt(arg.length() - 1) != 'i') {
            throw new NumberFormatException("Invalid input! Format: a+b*i / a-b*i");
        }
        if (arg.charAt(arg.length() - 2) != '*' && arg.charAt(arg.length() - 2) != '+' && arg.charAt(arg.length() - 2) != '-') {
            throw new NumberFormatException("Invalid input! Format: a+b*i / a-b*i");
        }
        String[] tokens = arg.split("[+]");
        if (tokens.length > 2) {
            throw new NumberFormatException("Invalid input! Format: a+b*i / a-b*i");
        }
        else if (tokens.length == 2) {
            if (tokens[0].charAt(0) == '-') {
                Re = Double.parseDouble(tokens[0].substring(1));
                Re *= -1;
            }
            else {
                Re = Double.parseDouble(tokens[0]);
            }
            if (tokens[1].length() == 1) {
                Im = 1;
            }
            else {
                Im = Double.parseDouble(tokens[1].substring(0, tokens[1].length() - 2));
            }
        }
        else {
            if (arg.charAt(0) == '-') {
                Re = -1;
                arg = arg.substring(1);
            } else {
                Re = 1;
            }
            tokens = arg.split("-");
            if (tokens.length != 2) {
                throw new NumberFormatException("Invalid input! Format: a+b*i / a-b*i");
            }
            Re *= Double.parseDouble(tokens[0]);
            Im = -1;
            if (tokens[1].length() > 1) {
                Im = -1 * Double.parseDouble(tokens[1].substring(0, tokens[1].length() - 2));
            }
        }
        return new ComplexNumber(Re, Im);
    }

    private static ComplexNumber[] getNumbers(String[] args) throws ArithmeticException {
        ComplexNumber[] numbers = new ComplexNumber[(args.length + 1) / 2];
        for (int i = 0; i < args.length; i += 2) {
            numbers[i / 2] = complexStringToNumber(args[i]);
        }
        return numbers;
    }

    public static ComplexExpression createExpression(String[] args) throws ArithmeticException {
        if (args.length % 2 != 1) {
            throw new ArithmeticException("Invalid number of arguments!");
        }
        return ExpressionFactory.getInstance().createExpression(getOperation(args), getNumbers(args));
    }
}
