package factory;

import domain.ComplexNumber;
import domain.Operation;
import expression.*;

public class ExpressionFactory {
    private static ExpressionFactory instance = new ExpressionFactory();

    private ExpressionFactory() {}
    public static ExpressionFactory getInstance() {
        return instance;
    }
    public ComplexExpression createExpression(Operation operation, ComplexNumber[] args) {
        if (operation == Operation.ADDITION) {
            return new AdditionExpression(operation, args);
        }
        else if (operation == Operation.SUBSTRACTION) {
            return new SubstractionExpression(operation, args);
        }
        else if (operation == Operation.MULTIPLICATION) {
            return new MultiplicationExpression(operation, args);
        }
        else if (operation == Operation.DIVISION) {
            return new DivisionExpression(operation, args);
        }
        else {
            return null;
        }
    }
}
