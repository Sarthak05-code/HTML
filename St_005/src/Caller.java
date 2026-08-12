public class Caller {

    public static void main(String[] args) {
        Answer ans = new Answer();
        ans.getCaller();
        ans.getCaller();
        ans.getCaller();
        int number = Answer.returnCounter();
        System.out.println("The number is : " + number);
        
    }
}

class Answer implements Class {

    static int callCounter = 0;

    @Override
    public void getCaller() {
        callCounter++;
        System.out.println("Your call was answered");
    }

    public static int returnCounter() {
        return callCounter;
    }
}

interface Class {
    public void getCaller();
}
