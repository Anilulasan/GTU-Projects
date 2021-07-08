import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.*;
public class Trader implements User{
    private String id;
    private String password;
    private String name;
    private LinkedList<Product> products;

    public Trader() {
        password = "trader";
        products = new LinkedList<>();
    }

    public Trader(String name, String ID) {
        this.name = name;
        this.id = ID;
        password = "trader";
        products = new LinkedList<>();
    }

    @Override
    public void setID(String id) {
        this.id = id;
    }

    @Override
    public void setPassword(String password) {
        this.password = password;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String getID() {
        return this.id;
    }

    @Override
    public String getPassword() {
        return this.password;
    }

    public String getName() {
        return this.name;
    }

    @Override
    public boolean equals(Object obj) {
        final Trader t2 = (Trader)obj;
        return this.name.equals(t2.getName());
    }

    public void addToProducts(Product p) {
        products.add(p);
    }

    public void writeProductsToFile(BufferedWriter bw) {
            sortByNames();
            for (Product p : products) {
                try {
                    bw.write(String.valueOf(p));
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

    }

    public void sortByNames() {
        int i;
        boolean exchange;
        do {
            exchange = false;
            for (i = 0; i < products.size()-1; i++) {
                if (products.get(i).getName().compareTo(products.get(i+1).getName()) < 0) {
                    exchange = true;
                    Product temp = products.get(i);
                    products.set(i, products.get(i+1));
                    products.set(i+1, temp);
                }
            }
        }while(exchange);
    }

    public void clearProducts() {
        products.clear();
    }

    public void addProduct() {
        Product p = new Product();
        Scanner scan = new Scanner(System.in);
        System.out.println("Please enter the ID of the product.");
        p.setId(scan.nextLine());
        System.out.println("Please enter the name of the product.");
        p.setName(scan.nextLine());
        System.out.println("Please enter the category tree of the product.");
        p.setCategory(scan.nextLine());
        System.out.println("Please enter the description of the product.");
        p.setDescription(scan.nextLine());
        System.out.println("Please enter the price of the product.");
        p.setPrice(scan.nextInt());
        System.out.println("Please enter the discount of the product.");
        p.setDiscount(scan.nextDouble());
        products.add(p);
    }

    public void show_products() {
        int index = 0;
        Iterator iter = products.iterator();
        while (iter.hasNext()) {
            System.out.println(index+"."+iter.next()+"\n");
            index++;
        }
    }

    public boolean removeProduct() {
        show_products();
        int choice;
        Scanner scan = new Scanner(System.in);
        System.out.println("Please enter the index of the product that you want to remove: ");
        choice = scan.nextInt();
        if (choice < 0 || choice >= products.size()) {
            System.out.println("Invalid index.");
            return false;
        }
        products.remove(choice);
        return true;
    }

    public boolean editProduct() {
        show_products();
        int index, choice;
        Scanner scan = new Scanner(System.in);
        System.out.println("Please enter the index of the item that you want to edit: ");
        index = scan.nextInt();
        if (index < 0 || index >= products.size()) {
            System.out.println("Invalid index.");
            return false;
        }
        do {
            System.out.println("1.Edit name\n" +
                    "2.Edit description\n" +
                    "3.Edit price\n" +
                    "4.Edit discount\n" +
                    "5.Exit\n");
            choice = scan.nextInt();
            switch (choice) {
                case 1:
                    System.out.println("Please enter the new name: ");
                    products.get(index).setName(scan.nextLine());
                    break;
                case 2:
                    System.out.println("Please enter the new description: ");
                    products.get(index).setDescription(scan.nextLine());
                    break;
                case 3:
                    System.out.println("Please enter the new price: ");
                    products.get(index).setPrice(scan.nextInt());
                    break;
                case 4:
                    System.out.println("Please enter the new discount: ");
                    products.get(index).setDiscount((scan.nextDouble()));
                    break;
                case 5:
                    return true;
                default:
                    System.out.println("Invalid choice.");

            }
        }while (choice != 5);
        return true;
    }

    public void show() {
        for (Product p: products)
            System.out.println(p.getName());
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(id+"/"+name+"\n");
        return sb.toString();
    }
}
