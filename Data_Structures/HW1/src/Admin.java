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
            if (choice < 1 || choice > 4) {
                System.out.println("Invalid entry. Please try again.\n");
            }
        } while (choice < 1 || choice > 4);
        return choice;
    }

    @Override
    public String toString() {
        return String.format(name + " " + surname + "\n" +
                id + "\n");
    }
}
