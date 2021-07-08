import java.util.Scanner;

public class Admin extends AuthorizedUser {

    public Admin(String name_i, String surname_i, String id_i, String password_i) {
        this.set_name(name_i);
        this.set_surname(surname_i);
        this.set_id(id_i);
        this.set_password(password_i);

    }

    @Override
    public int menu() {
        int choice;
        do {
            System.out.println("1. Add new branch\n" +
                    "2. Remove a branch\n" +
                    "3. Supply products\n" +
                    "4. Add Employee\n" +
                    "5. Exit\n" +
                    "Choice: ");
            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();
            if (choice < 1 || choice > 5) {
                System.out.println("Invalid entry. Please try again.\n");
            }
        } while (choice < 1 || choice > 5);
        return choice;
    }

    public boolean add_branch(KWLinkedList<Branch> branches) {
        boolean success = true;
        System.out.println("Please enter where you want to open a new branch: ");
        Scanner scan = new Scanner(System.in);
        String b_name = scan.nextLine();
        branches.addLast(new Branch(b_name, "Tom"));
        return success;

    }

    public void remove_branch(KWLinkedList<Branch> branches) {
        System.out.println("Please enter the branch you want to delete: ");
        Scanner scan = new Scanner(System.in);
        int index = scan.nextInt() - 1;
        if (index < 0 || index > branches.getSize())
            System.out.println("Invalid entry. ");
       branches.remove(index);
    }
    public void supply_products(KWLinkedList<Branch> branches) {
        System.out.println("Please choose a branch: ");
        Scanner scan = new Scanner(System.in);
        int index = scan.nextInt();
        if (index < 0 || index > branches.getSize()) {
            System.out.println("Invalid entry.");
        }
        branches.get(index-1).show_furnitures(1);
    }

    public boolean add_employee(KWLinkedList<Branch> branches, KWArrayList<Employee> employees) {
        boolean valid = true;
        System.out.println("Please enter the branch you want to add employee: ");
        Scanner scan = new Scanner(System.in);
        int choice = scan.nextInt();
        if (choice < 0 ||choice > branches.getSize()) {
            System.out.println("Invalid entry. ");
            valid = false;
        }
        else {
            System.out.println("Please enter the name of the employee: ");
            String name = scan.nextLine();
            System.out.println("Please enter the lastname of the employee: ");
            String surname = scan.nextLine();
            Employee e = new Employee(name, surname, create_id("E", employees.getSize()), "emp", branches.get(choice).get_name());
            employees.add(e);
        }
        return valid;
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

    @Override
    public String toString() {
        return String.format(name + " " + surname + "\n" +
                id + "\n");
    }
}
