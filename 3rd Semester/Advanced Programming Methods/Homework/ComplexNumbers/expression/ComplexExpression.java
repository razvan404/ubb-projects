package expression;

import java.util.Arrays;
import java.util.Vector;
import domain.ComplexNumber;
import domain.Operation;

public abstract class ComplexExpression {
    private Operation op;
    Vector<ComplexNumber> args;

    public ComplexExpression(Operation op, ComplexNumber[] numbers) {
        this.op = op;
        args = new Vector<ComplexNumber>();
        args.addAll(Arrays.asList(numbers));
    }

    public abstract void executeOneOperation();

    public ComplexNumber execute() {
        while (args.size() > 1) {
            executeOneOperation();
        }
        return args.elementAt(0);
    }
}
