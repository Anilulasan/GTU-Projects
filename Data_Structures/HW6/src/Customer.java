public class Customer implements User{

    private String id;
    private String password;

    public Customer(String id, String password) {
        setID(id);
        setPassword(password);
    }

    @Override
    public void setID(String id) {
        this.id = id;
    }

    @Override
    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String getID() {
        return this.id;
    }

    @Override
    public String getPassword() {
        return this.password;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(id+"\n");
        return sb.toString();
    }
}
