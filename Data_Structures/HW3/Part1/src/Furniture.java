public class Furniture {
    protected HybridList<Integer> furns;
    protected int model_count;

    public Furniture() {
        furns = new HybridList<>();
    }

    public Furniture(int model_c) {
        furns = new HybridList<>();
        model_count = model_c;
        for (int i = 0; i < model_count; i++) {
            furns.add(0);
        }
    }

    public int getModelCount() {
        return model_count;
    }

    public int getCount(int model) {
        return furns.get(model);
    }

    public void setCount(int index, int value) {
        furns.set(index, value);
    }

    public void increaseCount(int index, int value) {
        int num = furns.get(index);
        num += value;
        furns.set(index, num);
    }

    public void decreaseCount(int index, int value) {
        int num = furns.get(index);
        num -= value;
        if (num < 0)
            num = 0;
        furns.set(index, num);
    }

}
