import java.util.Scanner;

public class Customer implements User {
    private String name;
    private String surname;
    private String id;
    private String e_mail;
    private String password;


    public Customer(String name_i, String surname_i, String id_i, String mail, String password_i) {
        this.set_name(name_i);
        this.set_surname(surname_i);
        this.set_id(id_i);
        this.set_e_mail(mail);
        this.set_password(password_i);
    }


    @Override
    public void set_name(String name_i) {
        name = name_i;
    }

    @Override
    public void set_surname(String surname_i) {
        surname = surname_i;
    }

    @Override
    public void set_id(String id_i) {
        id = id_i;
    }

    public void set_e_mail(String mail) {
        e_mail = mail;
    }

    @Override
    public void set_password(String password_i) {
        password = password_i;
    }

    @Override
    public String get_name() {
        return name;
    }

    @Override
    public String get_surname() {
        return surname;
    }

    @Override
    public String get_id() {
        return id;
    }

    @Override
    public String get_password() {
        return password;
    }

    public int menu() {
        return 0;
    }

    public int search_products(KWLinkedList<Branch> branches) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Please choose a branch: ");
        int choice = scan.nextInt();
        if (choice < 0 ||choice > branches.getSize())
            System.out.println("Invalid entry");
        else {
            branches.get(choice-1).show_furnitures(2);
        }
        return choice;
    }

    @Override
    public String toString() {
        return String.format(name + " " + surname + "\n" +
                id + "\n");
    }
}
