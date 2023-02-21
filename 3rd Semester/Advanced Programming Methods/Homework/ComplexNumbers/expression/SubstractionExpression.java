package expression;

import domain.ComplexNumber;
import domain.Operation;

public class SubstractionExpression extends ComplexExpression {
    public SubstractionExpression(Operation op, ComplexNumber[] numbers) {
        super(op, numbers);
    }

    @Override
    public void executeOneOperation() {
        args.set(0, args.elementAt(0).subtract(args.elementAt(1)));
        args.remove(1);
    }
}
