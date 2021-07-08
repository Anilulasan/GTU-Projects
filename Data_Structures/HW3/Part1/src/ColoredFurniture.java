public class ColoredFurniture extends Furniture {
    private HybridList<HybridList<Integer>> furns;
    private int color_count;

    public ColoredFurniture(int model_c, int color_c) {
        int i;
        furns = new HybridList<>();
        model_count = model_c;
        color_count = color_c;
        HybridList<Integer> temp = new HybridList<>();
        for (i = 0; i < color_count; i++) {
            temp.add(0);
        }

        for (i = 0; i <model_count; i++) {
            furns.add(temp);
        }
    }

    public void setCount(int index1, int index2, int value) {
        furns.get(index1).set(index2, value);
    }

    public int getCount(int index1, int index2) {
        return furns.get(index1).get(index2);
    }

    public int getSize() {
        return furns.getSize();
    }

    public int getSize(int index) {
        return furns.get(index).getSize();
    }
}
