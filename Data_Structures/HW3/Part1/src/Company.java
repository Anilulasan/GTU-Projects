import java.util.Scanner;

public class Company{
    private KWLinkedList<Branch> branches;
    private KWArrayList<Admin> admins;
    private KWArrayList<Employee> employees;
    private KWArrayList<Customer> customers;

    public Company() {
        branches = new KWLinkedList<>();
        admins = new KWArrayList<>();
        employees = new KWArrayList<>();
        customers = new KWArrayList<>();
        admins.add(new Admin("Anil", "Ulasan", "A001", "admin"));

        branches.addLast(new Branch("Istanbul", create_id("E", employees.getSize())));
        branches.addLast(new Branch("Izmir", create_id("E", employees.getSize())));
    }

    public void menu() {
        int choice;
        do {
            System.out.print("Welcome to our Furniture Shop!\n\n" +
                    "1. Login\n" +
                    "2. Register\n" +
                    "3. Exit\n" +
                    "Choice: ");
            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();

            boolean reg_success;
            int type;
            int[] index;
            index = new int[1];
            if (choice == 1) {
                type = this.login(index);
                if (type == 0)
                    admin_menu(index[0]);
                else if (type == 1)
                    employee_menu(index[0]);
                else if (type == 2)
                    customer_menu(index[0]);

            } else if (choice == 2)
                reg_success = this.register();
        }while (choice != 3);
    }

    public int login(int[] index) { //Array because it needs to change in caller function.
        int type = -1;
        Scanner scan = new Scanner(System.in);
        String user_id, password;
        System.out.println("Please enter your ID: ");
        user_id = scan.nextLine();
        System.out.println("Please enter your password: ");
        password = scan.nextLine();
        index[0] = this.check(user_id, password);
        if (index[0] == -1) {
            System.out.println("Invalid id/password. Please try again.\n");
        }
        else {
            if (user_id.charAt(0) == 'A')
                type = 0;
            else if (user_id.charAt(0) == 'E')
                type = 1;
            else
                type = 2;
        }
        return type;
    }

    public int check(String user_id, String password) {
        int index;
        char type;
        type = user_id.charAt(0);
        index = id_check(user_id, type);
        if (type == 'A') {
            if (index != -1 && password.equals(admins.get(index).get_password())) {
                System.out.println("You have successfully entered the shop.\n" + admins.get(index));
                admins.get(index);
            }
        }
        else if(type == 'E') {
            if (index != -1 && password.equals(employees.get(index).get_password())) {
                System.out.println("You have successfully entered the shop.\n" + employees.get(index));
                this.employee_menu(index);
            }
        }
        else if(type == 'C') {
            if (index != -1 && password.equals(customers.get(index).get_password())) {
                System.out.println("You have successfully entered the shop.\n" + customers.get(index));
                this.customer_menu(index);
            }
        }
        return index;
    }

    public int id_check(String user_id, char type) {
        int i, index = -1;
        boolean found = false;
        if (type == 'A') {
            for (i = 0; i < admins.getSize() & !found; i++) {
                if (user_id.equals(admins.get(i).get_id())) {
                    index = i;
                    found = true;
                }
            }
        }
        if (type == 'E') {
            for (i = 0; i < employees.getSize() & !found; i++) {
                if (user_id.equals(employees.get(i).get_id())) {
                    index = i;
                    found = true;
                }
            }
        }
        if (type == 'C') {
            for (i = 0; i < customers.getSize() & !found; i++) {
                if (user_id.equals(customers.get(i).get_id())) {
                    index = i;
                    found = true;
                }
            }
        }
        return index;
    }

    public boolean register() {
        boolean valid = true;
        Scanner scan = new Scanner(System.in);
        String name, surname, id, mail, password;
        System.out.println("Please enter your name: ");
        name =  scan.nextLine();
        System.out.println("Please enter your surname: ");
        surname =  scan.nextLine();
        System.out.println("Please enter your e-mail: ");
        mail =  scan.nextLine();
        System.out.println("Please enter your password: ");
        password =  scan.nextLine();
        id = this.create_id("C", customers.getSize());
        Customer c = new Customer(name, surname, id,mail, password);
        customers.add(c);
        this.customer_menu(customers.getSize()-1);
        return valid;
    }

    public void show_branches() {
        int i;
        for (i = 0; i < branches.getSize(); i++) {
            System.out.printf("%d. %s", i+1, branches.get(i));
        }
    }

    public String create_id(String type, int number) {
        String id = type;
        if (number+1 < 10) {
            id += "00";
        }
        else if (number+1 < 100)
            id += "0";
        id += Integer.toString(number+1);
        return id;
    }

    public void add_branch(String name, String emp_id) {
        Branch b = new Branch(name, emp_id);
        branches.addLast(b);
        employees.add(b.get_emp());
    }

    public void admin_menu(int index) {
        int selection;
        do {
            selection = admins.get(index).menu();
            switch (selection) {
                case 1:
                    show_branches();
                    admins.get(index).add_branch(branches);
                    break;
                case 2:
                    show_branches();
                    admins.get(index).remove_branch(branches);
                    break;
                case 3:
                    show_branches();
                    admins.get(index).supply_products(branches);
                    break;
                case 4:
                    show_branches();
                    admins.get(index).add_employee(branches, employees);
                    break;
            }
            if (selection < 1 || selection > 4)
                System.out.println("Please enter where you want to open a new branch: ");
        }while (selection != 5);
    }

    public void employee_menu(int index) {
        int choice;
        do {
            System.out.println("1. Inform admin\n" +
                    "2. Update orders" +
                    "3. Exit\n" +
                    "Choice: ");
            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();
            switch (choice) {
                case 1:
                    System.out.println("Admin has been informed about supplies. "); break;
                case 2: System.out.println("Previous orders has been updated.  "); break;
            }
        }while (choice != 3);
    }

    public void customer_menu(int index) {
        int choice, branch_index = -1;
        do {
            System.out.println("1. Search products\n" +
                    "2. Buy products\n" +
                    "3. Exit\n" +
                    "Choice: ");
            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();
            switch (choice) {
                case 1:
                    show_branches();
                    branch_index = customers.get(index).search_products(branches); break;
                case 2:
                    buy_products(branch_index); break;
            }
        }while (choice != 3);
    }

    public void buy_products(int branch_index) {
        if (branch_index == -1)
            System.out.println("Please search for products first.");
        else {
            branches.get(branch_index).show_furnitures(2);
            Scanner scan = new Scanner(System.in);
            System.out.println("Please enter how many pieces do you want.");
            int index = scan.nextInt();
            System.out.println("Cargo delivered.");
        }
    }

    public void remove_branch(int index) {
        branches.remove(index);
    }

}
