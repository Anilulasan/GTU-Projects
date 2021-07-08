import java.util.Scanner;

public class Branch {
    private String name;
    private ColoredFurniture chairs;
    private ColoredFurniture desks;
    private ColoredFurniture tables;
    private Furniture  bookcases;
    private Furniture cabinets;
    Employee branch_emp;

    public Branch(String name, String emp_id) {
        this.name = name;
        branch_emp = new Employee("Mehmet", "Yıldız", emp_id, "yildiz1", this.name);
        chairs = new ColoredFurniture(5, 10);
        desks = new ColoredFurniture(3, 8);
        tables = new ColoredFurniture(7, 5);
        bookcases = new Furniture(7);
        cabinets = new Furniture(10);

        branch_emp.first_supply(chairs);
        branch_emp.first_supply(desks);
        branch_emp.first_supply(tables);
        branch_emp.first_supply(bookcases);
        branch_emp.first_supply(cabinets);
    }

    public String get_name() {
        return name;
    }

    public Employee get_emp() {
        return branch_emp;
    }

    public void show_furnitures(int opcode) {
        int choice;
        int selection = 0;
        do {
            System.out.println("1. Chairs\n" +
                    "2. Desks\n" +
                    "3. Tables\n" +
                    "4. Bookcases\n" +
                    "5. Cabinets\n" +
                    "6. Exit\n" +
                    "Choice: ");
            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt();
            if (choice < 0 || choice > 6)
                System.out.println("Invalid entry. Please try again.");
            switch (choice) {
                case 1:
                    selection = show_model(chairs);
                    break;
                case 2:
                    selection = show_model(desks);
                    break;
                case 3:
                    selection = show_model(tables);
                    break;
                case 4:
                    selection = show_model(bookcases);
                    break;
                case 5:
                    selection =  show_model(cabinets);
                    break;
            }
        }while (choice != 6 || selection != 0);
        if (opcode == 0) { //Add supply.
            System.out.println("Please enter the indexes and amount to add");
            Scanner scan = new Scanner(System.in);
            int choice1 = scan.nextInt();

        }
    }

    public int show_model(ColoredFurniture furniture) {
        int i, choice;
        boolean valid;
        do {
            valid = true;
            for (i = 0; i < furniture.getModelCount(); i++) {
                System.out.printf("%d. Model %d\n", i + 1, i + 1);
            }
            System.out.println("0. Back");
            System.out.println("Choice: ");
            Scanner scan = new Scanner(System.in);
            choice = scan.nextInt()-1;
            if (choice < 1 ||choice > furniture.getModelCount()) {
                System.out.println("Invalid entry. Please try again.");
                valid = false;
            }
        }while (valid == false);
        for (i = 0; i < furniture.getSize(choice); i++) {
            this.print_color(i);
            System.out.println("Piece: "+furniture.getCount(choice, i));
        }
        return choice;
    }

    public int show_model(Furniture furniture) {
        int i;
        for (i = 0; i < furniture.getModelCount(); i++) {
            System.out.printf("%d. Model %d, Piece: %d\n", i+1, i+1, furniture.getCount(i));
        }
        return 0;
    }

    public void print_color(int number) {
        switch (number) {
            case 0: System.out.println("Red "); break;
            case 1: System.out.println("Black "); break;
            case 2: System.out.println("White "); break;
            case 3: System.out.println("Blue "); break;
            case 4: System.out.println("Green "); break;
        }
    }

    @Override
    public String toString() {
        return String.format(""+name+"\n");
    }
}
