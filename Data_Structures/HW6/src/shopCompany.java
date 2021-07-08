import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Scanner;

public class shopCompany {
    //private ArrayList<Product> products;
    private final String traderBaseID = "1839";
    private final String customerBaseID = "9614";
    private ArrayList<Trader> traders;
    private Hashtable<String, Customer> customers;
    private ArrayList<Product> products;

    public shopCompany() {
        //products = new ArrayList();
        traders = new ArrayList<>();
        customers = new Hashtable<>();
        products = new ArrayList<>();
    }

    public void menu() {
        organizeFile();
        int choice;
        System.out.println("Welcome to Shopping Center!!!");
        do {
            System.out.println("1.Login\n" +
                    "2.Register\n" +
                    "3.Exit\n");

            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    register();
                    break;
                case 3:
                    break;
                default:
                    System.out.println("Invalid choice. Try again.\n\n");
            }
        }while (choice != 3);
    }

    public void traderMenu(int index) {

        int choice;
        boolean invalid;
        do {
            invalid = false;
            System.out.println("Welcome Trader: " +traders.get(index)+"\n"+
                    "1.Add product\n" +
                    "2.Remove product\n" +
                    "3.Edit a product\n" +
                    "4.Exit\n");

            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();
            switch (choice) {
                case 1:
                    traders.get(index).addProduct();
                    break;
                case 2:
                    traders.get(index).removeProduct();
                    break;
                case 3:
                    traders.get(index).editProduct();
                    break;
                case 4:
                    break;
                default:
                    invalid = true;
                    System.out.println("Invalid choice. Try again.\n\n");
            }
        }while (invalid || choice != 4);
    }

    public boolean customerMenu(int index) {
        int choice;
        boolean invalid;
        do {
            invalid = false;
            System.out.println("Welcome Customer: " +customers.get(index)+"\n"+
                    "1.Search Products\n" +
                    "2.Search Traders\n" +
                    "3.Exit\n");

            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();
            switch (choice) {
                case 1:
                    searchProducts();
                    break;
                case 2:
                    break;
                case 3:
                    traders.get(index).editProduct();
                    break;
                case 4:
                    break;
                default:
                    invalid = true;
                    System.out.println("Invalid choice. Try again.\n\n");
            }
        }while (invalid || choice != 3);
        return true;
    }

    private int searchProducts() {
        int choice;
        boolean invalid;
        do {
            invalid = false;
            System.out.println("1.Sort by name(Ascending order)\n" +
                    "2.Sort by name(Descending order)\n" +
                    "3.Sort by price(Ascending order)\n" +
                    "4.Sort by price(Descending order)\n" +
                    "5.Sort by discount(Ascending order)\n" +
                    "6.Sort by discount(Descending order)\n" +
                    "7.Filter with category\n" +
                    "8.Filter with price interval\n" +
                    "9.Exit\n");

            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();
            switch (choice) {
                case 1:
                    sortByName(0);
                    break;
                case 2:
                    sortByName(1);
                    break;
                case 3:
                    sortByPrice(0);
                    break;
                case 4:
                    sortByPrice(1);
                    break;
                case 5:
                    sortByDiscount(1);
                    break;
                case 6:
                    sortByDiscount(1);
                    break;
                case 7:
                    listByCategory();
                    break;
                case 8:
                    searchByInterval();
                    break;
                case 9:
                    break;
                default:
                    invalid = true;
                    System.out.println("Invalid choice. Try again.\n\n");
            }
        }while (invalid || choice != 9);
        return 0;
    }

    private void sortByName(int direction) {
        int i;
        boolean exchange;
        do {
            exchange = false;
            for (i = 0; i < products.size()-1; i++) {
                if ((direction == 0 && products.get(i).getName().compareTo(products.get(i+1).getName()) < 0) || (direction == 1 && products.get(i).getName().compareTo(products.get(i+1).getName()) > 0)) {
                    exchange = true;
                    Product temp = products.get(i);
                    products.set(i, products.get(i+1));
                    products.set(i+1, temp);
                }
            }
        }while(exchange);
    }

    private void sortByPrice(int direction) {
        if (direction == 0) {
            int max, max_index;
            for (int i = 0; i < products.size(); i++) {
                max = products.get(i).getPrice();
                max_index = i;
                for (int j = i; j < products.size(); j++) {
                    if (products.get(j).getPrice() > max) {
                        max = products.get(j).getPrice();
                        max_index = j;
                    }
                }
                Product temp = products.get(i);
                products.set(i, products.get(max_index));
                products.set(max_index, temp);
            }
        }
        else {
            int min, min_index;
            for (int i = 0; i < products.size(); i++) {
                min = products.get(i).getPrice();
                min_index = i;
                for (int j = i; j < products.size(); j++) {
                    if (products.get(j).getPrice() > min) {
                        min = products.get(j).getPrice();
                        min_index = j;
                    }
                }
                Product temp = products.get(i);
                products.set(i, products.get(min_index));
                products.set(min_index, temp);
            }
        }
    }

    private void sortByDiscount(int direction) {

    }

    private void listByCategory() {
        System.out.println("Please enter the category you want to search: ");
        Scanner scan = new Scanner(System.in);
        String cat = scan.nextLine();
        int index = 0;
        for (Product p: products) {
            if (p.getCategory().contains(cat))
                System.out.println(index+"."+p);

            index++;
        }
    }

    private void searchByInterval() {
        int low, up;
        Scanner scan = new Scanner(System.in);
        System.out.println("Please enter the lower bound");
        low = scan.nextInt();
        System.out.println("Please enter the upper bound");
        up = scan.nextInt();
        int index = 0;
        for (Product p: products) {
            if (p.getPrice() <= low && p.getPrice() >= up)
                System.out.println(index+"."+p);

            index++;
        }
    }

    public boolean login() {
        String id, password;
        Scanner scan = new Scanner(System.in);
        System.out.println("Please enter your ID: ");
        id = scan.nextLine();
        System.out.println("Please enter your password: ");
        password = scan.nextLine();

        int index = isValid(id, password);
        if (index == -1) {
            System.out.println("Invalid ID/password. ");
            return false;
        }
        if (id.contains(traderBaseID))
            traderMenu(index);

        else
            customerMenu(index);
        return true;
    }

    private int isValid(String id, String password) {
        int result = -1, index = 0;
        if (id.contains(traderBaseID)) {
            for (Trader t : traders) {
                if (t.getID().equals(id)) {
                    if (t.getPassword().equals(password))
                        return index;
                    return -1;
                }
                index++;
            }
        }
        else if (id.contains(customerBaseID)) {
            if (customers.get(id) == null)
                return -1;
            else if(customers.get(id).equals(password)){
                return 0;
            }
        }
        return -1;
    }

    public boolean register() {
        String password, id = createID('C', customers.size());
        System.out.println("You are given an id = "+id);

        Scanner scan = new Scanner(System.in);
        boolean invalid;
        do {
            System.out.println("Please type a password: ");
            invalid = false;
            password = scan.nextLine();
            if (password.length() != 6) {
                invalid = true;
                System.out.println("Password must consist of 6 characters. Try again\n\n");
            }
        }while (invalid);

        Customer c = new Customer(id, password);
        customers.put(id, c);
        writeCustomersToFile();
        return true;
    }

    public boolean organizeFile() {
        try {
            FileReader fr = new FileReader("e-commerce-samples.csv");
            BufferedReader csvReader = new BufferedReader(fr);

           csvReader.readLine();

            String row;
            while ((row = csvReader.readLine()) != null) {
                System.out.println(row);
                String[] temp = row.split(";", 7);

                //Set product's infoes.
                Product p = new Product();
                p.setId(temp[0]);
                p.setName(temp[1]);
                p.setCategory(temp[2]);
                p.setPrice(Integer.parseInt(temp[3]));
                double price_d = p.getPrice();
                p.setDiscount((price_d - Double.parseDouble(temp[4]))/p.getPrice());
                p.setDescription(temp[5]);
                p.setTraderName(temp[6]);
                //If trader is new.
                int traderIndex = findTrader(traders, temp[6]);
                if (traderIndex == -1) {
                    Trader t = new Trader(temp[6], createID('T', traders.size()));
                    t.addToProducts(p);
                    traders.add(t);
                }
                //If trader is already added to system.
                else
                    traders.get(traderIndex).addToProducts(p);
            }
            csvReader.close();
            writeTradersToFile();

            writeProductsToFile();
        } catch (Exception FileNotFoundException) {
            System.out.println("Exception occured trying to open the file...");
        }
        traders.get(0).show();
        traders.get(25).show();
        return true;
    }

    private boolean writeTradersToFile() {
        if (traders.size() == 0)
            return false;
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter("traders.txt"));
            for (Trader t: traders)
                bw.write(String.valueOf(t));
            bw.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return true;
    }

    private boolean writeCustomersToFile() {
        if (customers.size() == 0)
            return false;
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter("customers.txt", true));
            bw.write(String.valueOf(customers.get(customers.size()-1)));
            bw.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return true;
    }

    private boolean writeProductsToFile() {
        if (traders.size() == 0)
            return false;
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter("products.txt"));
            for (Trader t: traders) {
               t.writeProductsToFile(bw);
               t.clearProducts();
            }
            bw.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return true;
    }

    //When reading the csv file, i check if the trader of the product
    // is already added to system.
    private int findTrader(ArrayList<Trader> traders, String name) {
        int index = 0;
        for (Trader t: traders) {
            if (t.getName().equals(name) == true)
                return index;
            index++;
        }
        return -1;
    }
    //I assigned 5-digit base ID s to traders and customers. Instead of generating
    //random values, i added a num based on when that trader added.
    //For ex: if base ID is "12345" and 5th trader added to system, its ID is "12345005".
    private String createID(char type, int size) {
        String id;
        if (type == 'T')
            id = traderBaseID;
        else
            id = customerBaseID;

        for (int i = 1; i < 4; i++) { //This loop for add '0' to id if digit is small.
            if (size+1 < Math.pow(10, 4-i))
                id += "0";
        }
        id += Integer.toString(size+1);
        return id;

    }
}
