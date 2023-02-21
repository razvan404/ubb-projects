package run;

import parser.ExpressionParser;

public class Main {
    public static void main(String[] args) {
        Tester.run();
        try {
            System.out.println(ExpressionParser.createExpression(args).execute().toString());
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}