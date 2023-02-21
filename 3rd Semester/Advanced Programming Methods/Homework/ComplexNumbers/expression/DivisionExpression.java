package expression;

import domain.ComplexNumber;
import domain.Operation;

public class DivisionExpression extends ComplexExpression {
    public DivisionExpression(Operation op, ComplexNumber[] numbers) {
        super(op, numbers);
    }

    @Override
    public void executeOneOperation() {
        args.set(0, args.elementAt(0).divide(args.elementAt(1)));
        args.remove(1);
    }
}
