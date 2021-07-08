import java.util.Scanner;

public class Main {
    public static void main(String []args) {
        Company shop_company = new Company();
        System.out.println("Welcome to our program. Please choose:\n" +
                "1. Menu\n" +
                "2. Driver\n" +
                "Choice: ");
        Scanner scan = new Scanner(System.in);
        int choice = scan.nextInt();
        if (choice == 1)
            shop_company.menu();
        else if (choice == 2)
            driver();
        else
            System.out.println("Try again later...");
    }

    public static void driver() {
        Company shop_company = new Company();
        System.out.println("--------------------------------------------");
        System.out.println("---------Login id check-----------");
        System.out.println("Trying to enter with id: A243, Password:asd");
        shop_company.check("A243", "sdf");
        System.out.println("Trying to enter with id: A001, Password:admin");
        shop_company.check("A001", "admin");
        System.out.println("---------Show Branches-----------");
        shop_company.show_branches();
        System.out.println("---------Add Branch-----------");
        shop_company.add_branch("Eskisehir", "E009");
        System.out.println("---------Show Branches-----------");
        shop_company.show_branches();
        System.out.println("---------Remove Branch-----------");
        shop_company.remove_branch(1);
        System.out.println("---------Show Branches-----------");
        shop_company.show_branches();
        System.out.println("---------Create id for new register.-----------");
        System.out.println(""+shop_company.create_id("C", 6));
        System.out.println("----------------------------------------------");
    }
}
