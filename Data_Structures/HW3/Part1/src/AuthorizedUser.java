public abstract class AuthorizedUser implements User {
    protected String name;
    protected String surname;
    protected String id;
    protected String password;

    public void set_name(String name_i) {
        this.name = name_i;
    }

    public void set_surname(String surname_i) {
        this.surname =  surname_i;
    }

    public void set_id(String id_i) {
        this.id = id_i;
    }

    public void set_password(String password_i) {
        this.password = password_i;
    }

    public String get_name() {
        return this.name;
    }

    public String get_surname() {
        return this.surname;
    }

    public String get_id() {
        return this.id;
    }

    public String get_password() {
        return this.password;
    }

    public abstract int menu();


}
