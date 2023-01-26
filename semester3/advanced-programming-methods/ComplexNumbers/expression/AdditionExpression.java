package expression;

import domain.ComplexNumber;
import domain.Operation;

public class AdditionExpression extends ComplexExpression {

    public AdditionExpression(Operation op, ComplexNumber[] numbers) {
        super(op, numbers);
    }

    @Override
    public void executeOneOperation() {
        args.set(0, args.elementAt(0).add(args.elementAt(1)));
        args.remove(1);
    }
}
