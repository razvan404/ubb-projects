package application.gui;

class A {
    static int x = 10;
    String y = "varianta ";
    public A() {
        y += "A ";
        x--;
    }

    public boolean equals(Object obj) {
        return ((A) obj).y.equals(y);
    }
}

class B extends A {
    String y = "varianta ";
    int z = x;
    public B() {
        y += "B ";
        z++;
    }

    public boolean equals(Object obj) {
        return ((B) obj).z == z;
    }
}

public class C {
    public static void main(String[] args) {
        A a = new B();
        B b = new B();
        System.out.println(a.y);
        System.out.println(b.y);
        System.out.println(a.x);
        System.out.println(((B) a).z);
        System.out.println(b.z);
        System.out.println(a == b);
        System.out.println(b.equals(a));
        System.out.println(a.equals(b));
        System.out.println(b instanceof A);
        System.out.println(b.getClass().getSuperclass().getName());
    }
}
