public class Binary {

    public static void main(String[] args) {
        var customer = new Customer("101", "Sarthak", "9851136656");

        var order = new Order(customer, "101", ItemsStock.JUICE, 5);

        var bill = new FinalBill(customer, order);

        bill.pricePerProduct();
    }
}

// Product Enum
enum ItemsStock {
    APPLE,
    ORANGE,
    POTATO,
    SPICES,
    PEAS,
    JUICE,
    YOGURT,
    CARBONATED_DRINK,
    BEETROOT,
}

// Customer Info
record Customer(
    String customerID,
    String customerName,
    String customerNumber
) {}

// Customer's Order Info
record Order(
    Customer customer,
    String itemID,
    ItemsStock itemName,
    int quantity
) {}

// Final Bill
record FinalBill(Customer customer, Order order) {
    public void pricePerProduct() {
        // Unit prices are in NPR, per kg or litre depending on the product.
        var price = switch (order.itemName()) {
            case APPLE -> 120.0;
            case JUICE -> 100.0;
            case POTATO -> 105.0;
            case SPICES -> 55.0;
            case PEAS -> 35.0;
            case YOGURT -> 85.0;
            case CARBONATED_DRINK -> 105.0;
            case ORANGE -> 98.0;
            case BEETROOT -> 75.0;
            default -> 100.0;
        };

        var total = price * order.quantity();

        System.out.println("ItemName: " + order.itemName());
        System.out.println("Price per item: " + price);
        System.out.println("Quantity: " + order.quantity());
        System.out.println("Total: " + total);
    }
}
