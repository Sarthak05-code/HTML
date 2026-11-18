import java.util.ArrayList;

public class Binary {

    public static void main(String[] args) {
        var storage = new Storage(101, "Powdered Sugar", 5, new ArrayList<>());
        storage.items().add(10);
        storage.items().add(20);
        storage.items().add(30);
        storage.items().add(40);
        storage.items().add(50);

        System.out.printf(
            "Item ID: %d , ItemName : %s , Item quantity : %d\n",
            storage.ID(),
            storage.ItemName(),
            storage.quantity()
        );
        System.out.print("Items list : ");
        for (var item : storage.items()) {
            System.out.print(item + " ");
        }
    }
}

record Storage(
    int ID,
    String ItemName,
    int quantity,
    ArrayList<Integer> items
) {}
