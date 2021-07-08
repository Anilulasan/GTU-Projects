public class Product {
    private String id;
    private String category;
    private String name;
    private String description;
    private int price;
    private double discount;
    private String traderName;

    public Product() {

    }

    public void setId(String ID) {
        this.id = ID;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public void setDiscount(double dc) {
        this.discount = dc;
    }

    public void setTraderName(String tName) {this.traderName = tName;}

    public String getId() {
        return id;
    }

    public String getCategory() {
        return category;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public int getPrice() {
        return price;
    }

    public double getDiscount() {
        return discount;
    }

    public String getTraderName() {return traderName;}

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        /*sb.append("ID: "+id+ "\n");
        sb.append("Name: "+name+"\n");
        sb.append("Category: "+category+"\n");
        sb.append("Description: "+description+"\n");
        sb.append("Price = "+price+"\n");
        sb.append("Discounted price="+price*discount+"\n");
        sb.append("Trader: "+traderName+"\n");*/
        sb.append(id+"/"+name+"/"+category+"/"+price+"/"+price*discount+"\n");
        return sb.toString();
    }
}
