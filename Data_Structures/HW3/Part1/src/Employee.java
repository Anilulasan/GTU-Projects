public class Employee extends AuthorizedUser{
    private String branch_name;
    private final int DEF_PIECE = 5;

    public Employee(String name_i, String surname_i, String id_i, String password_i, String branch_i) {
        this.set_name(name_i);
        this.set_surname(surname_i);
        this.set_id(id_i);
        this.set_password(password_i);
        this.set_branch_name(branch_i);
    }

    public void set_branch_name(String branch_i) {
        branch_name = branch_i;
    }

    @Override
    public String toString() {
        return String.format(name + " " + surname + "\n" +
                id + "\n" +
                branch_name + "\n");
    }

    @Override
    public int menu() {
        return 0;
    }

    public void first_supply(Furniture furn) {
        int i;
        for (i = 0; i < furn.getModelCount(); i++) {
            furn.setCount(i, DEF_PIECE);
        }
    }

    public void first_supply(ColoredFurniture furn) {
        int i, j;
        for (i = 0; i < furn.getSize(); i++) {
            for (j = 0; j < furn.getSize(i); j++) {
                furn.setCount(i, j, DEF_PIECE);
            }
        }
    }

    public void remove_supply(Furniture furn, int index, int amount) {
        furn.decreaseCount(index, amount);
    }

    public void add_supply(Furniture furn, int index, int number) {
        furn.setCount(index, number);
    }

    public void add_supply(ColoredFurniture furn, int index1, int index2, int number) {
        furn.setCount(index1, index2, number);
    }
}
