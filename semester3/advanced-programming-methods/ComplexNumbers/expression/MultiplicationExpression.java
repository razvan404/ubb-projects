package expression;

import domain.ComplexNumber;
import domain.Operation;

public class MultiplicationExpression extends ComplexExpression {
    public MultiplicationExpression(Operation op, ComplexNumber[] numbers) {
        super(op, numbers);
    }

    @Override
    public void executeOneOperation() {
        args.set(0, args.elementAt(0).multiply(args.elementAt(1)));
        args.remove(1);
    }
}
