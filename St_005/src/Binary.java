
public class Binary {

    public static void main(String[] args) {
        var innerCircle = new Caller(). new InnerCaller();
        innerCircle.helloInner();

        var o = new OutmostCircle();
        var om = new OutmostCircle().new MiddleCircle();
        var omi = new OutmostCircle().new MiddleCircle().new InnerCircle();

        o.outmostCircleprint();
        om.middleCircleprint();
        omi.innerCircleprint();
        
    }
}

class Caller {
    class InnerCaller {
        public void helloInner() {
            System.out.println("Hello from Inner.");
        }
    }
}

/// triple nested class

class OutmostCircle {
    public void outmostCircleprint() {
        System.out.println("Hello from the outmost circle.");
    }
    class MiddleCircle {
        public void middleCircleprint() {
            System.out.println("Hello from the middle circle.");
        }
        class InnerCircle {
            public void innerCircleprint() {
                System.out.println("Hello from the innermost circle.");
            }
            
        }
    }
}