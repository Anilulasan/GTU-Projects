import java.util.Arrays;
import java.util.Scanner;

public class Company{
    private Branch[] branches;
    private Admin[] admins;
    private Employee[] employees;
    private Customer[] customers;
    private int admin_count;
    private int emp_count;
    private int cus_count;
    private int branch_count;
    private final int INC_CAP = 10;

    public Company() {
        admins = new Admin[5];
        employees = new Employee[10];
        branches = new Branch[10];
        customers = new Customer[10];
        admins[0] = new Admin("Anil", "Ulasan", "A001", "admin");

        this.add_branch("Istanbul", create_id("E", emp_count));
        this.add_branch("Izmir", create_id("E", emp_count));
    }

    public void increase_cap(User[] array) {
        array = Arrays.copyOf(array, array.length+INC_CAP);
    }

    public void increase_cap(Branch[] array) { 
        array = Arrays.copyOf(array, array.length+INC_CAP);
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
            if (choice == 1) {
                type = this.login();
                if (type == 0)
                    admin_menu();
                else if (type == 1)
                    employee_menu();
                else if (type == 2)
                    customer_menu();

            } else if (choice == 2)
                reg_success = this.register();
        }while (choice != 3);
    }

    public int login() {
        int type = -1;
        Scanner scan = new Scanner(System.in);
        String user_id, password;
        System.out.println("Please enter your ID: ");
        user_id = scan.nextLine();
        System.out.println("Please enter your password: ");
        password = scan.nextLine();
        int index = this.check(user_id, password);
        if (index == -1) {
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
        int index = -1;
        char type;
        type = user_id.charAt(0);
        if (type == 'A') {
            index = id_check(user_id, admins, admin_count);
            if (index != -1 && password.equals(admins[index].get_password())) {
                System.out.println("You have successfully entered the shop.\n" + admins[index]);
                this.admin_menu();
            }
        }
        else if(type == 'E')
            index = id_check(user_id, employees, emp_count);
        else if(type == 'C')
            index = id_check(user_id, customers, cus_count);
        return index;
    }

    public int id_check(String user_id, User[] array, int size) {
        int i, index = -1;
        boolean found = false;
        for (i = 0; i < size & !found; i++) {
            if (user_id.equals(array[i].get_id())) {
                index = i;
                found = true;
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
        id = this.create_id("C", customers.length);
        Customer c = new Customer(name, surname, id,mail, password);
        customers[cus_count] = c;
        cus_count++;
        this.customer_menu();
        return valid;
    }

    public void show_branches() {
        int i;
        for (i = 0; i < branch_count; i++) {
            System.out.printf("%d. %s", i+1, branches[i]);
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
        if (branch_count == branches.length)
            increase_cap(branches);
        branches[branch_count] = b;
        if (emp_count == employees.length)
            increase_cap(employees);
        employees[emp_count] = b.get_emp();
        branch_count++;
        emp_count++;
    }

    public void admin_menu() {
        int selection;
        do {
            selection = admins[0].menu();
            switch (selection) {
                case 1:
                    add_branch();
                    break;
                case 2:
                    remove_branch();
                    break;
                case 3:
                    supply_products();
                    break;
                case 4:
                    add_employee();
                    break;
            }
            if (selection < 1 || selection > 4)
                System.out.println("Please enter where you want to open a new branch: ");
        }while (selection != 4);
    }

    public void employee_menu() {
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

    public void customer_menu() {
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
                    branch_index = search_products(); break;
                case 2: buy_products(branch_index); break;
            }
        }while (choice != 3);
    }

    public int search_products() {
        show_branches();
        Scanner scan = new Scanner(System.in);
        System.out.println("Please choose a branch: ");
        int choice = scan.nextInt();
        if (choice < 0 ||choice > branch_count)
            System.out.println("Invalid entry");
        else {
            branches[choice].show_furnitures();
        }
        return choice;
    }

    public void buy_products(int branch_index) {
        if (branch_index == -1)
            System.out.println("Please search for products first.");
        else {
            branches[branch_index].show_furnitures();
            Scanner scan = new Scanner(System.in);
            System.out.println("Please enter how many pieces do you want.");
            int index = scan.nextInt();
            System.out.println("Cargo delivered.");
        }
    }

    public boolean add_branch() {
        boolean success = true;
        this.show_branches();
        System.out.println("Please enter where you want to open a new branch: ");
        Scanner scan = new Scanner(System.in);
        String b_name = scan.nextLine();
        this.add_branch(b_name, "Tom");
        branch_count++;
        return success;

    }

    public void remove_branch() {
        show_branches();
        System.out.println("Please enter the branch you want to delete: ");
        Scanner scan = new Scanner(System.in);
        int start_index = scan.nextInt() - 1;
        if (start_index < 0 || start_index > branch_count)
            System.out.println("Invalid entry. ");
        else {
            int i;
            for (i = start_index; i < branch_count - 1; i++) {
                branches[i] = branches[i + 1];
            }
            branch_count--;
        }
    }

    public void supply_products() {
        this.show_branches();
        System.out.println("Please choose a branch: ");
        Scanner scan = new Scanner(System.in);
        int index = scan.nextInt();
        branches[index-1].show_furnitures();
    }

    public boolean add_employee() {
        boolean valid = true;
        show_branches();
        System.out.println("Please enter the branch you want to add employee: ");
        Scanner scan = new Scanner(System.in);
        int choice = scan.nextInt();
        if (choice < 0 ||choice > branch_count) {
            System.out.println("Invalid entry. ");
            valid = false;
        }
        else {
            System.out.println("Please enter the name of the employee: ");
            String name = scan.nextLine();
            System.out.println("Please enter the name of the employee: ");
            String surname = scan.nextLine();
            Employee e = new Employee(name, surname, create_id("E", emp_count), "emp", branches[choice].get_name());
            employees[emp_count] = e;
            emp_count++;
        }
        return valid;
    }

}
