public class HybridList<E> {
    private final int MAX_NUMBER = 5;
    private KWLinkedList<KWArrayList<E>> list;
    private int size;
    private int sizeA;

    @SuppressWarnings("unchecked")
    public HybridList() {
        list = new KWLinkedList<>();
        KWArrayList<E> temp = new KWArrayList();
        list.addLast(temp);
        size = 0;
    }

    public E get(int index) {
        int num1 = index/MAX_NUMBER;
        int num2 = index%MAX_NUMBER;
        return list.get(num1).get(num2);
    }

    public void set(int index, E data) {
        int num1 = index/MAX_NUMBER;
        int num2 = index%MAX_NUMBER;
        list.get(num1).set(num2, data);
    }

    public void add(E obj) {
        if (size == MAX_NUMBER-1) {
            KWArrayList<E> temp = new KWArrayList();
            list.addLast(temp);
        }
        int num1 = size/MAX_NUMBER;
        int num2 = size%MAX_NUMBER;
        list.get(num1).add(num2, obj);
        size++;
    }

    public void shift(int index, int direction) {
        int index_l1, index_l2, index_a1, index_a2;
        if (direction == 0) {//Shift to left.
            int i = index;
            while (i < size - 1) {
                index_l1 = i / MAX_NUMBER;
                index_l2 = (i + 1) / MAX_NUMBER;
                index_a1 = i % MAX_NUMBER;
                index_a2 = (i + 1) % MAX_NUMBER;
                list.get(index_l1).set(index_a1, list.get(index_l2).get(index_a2));
                i++;
            }
        }
        else { //Shift to right.
            int i = size-1;
            while (i > index) {
                index_l1 = i / MAX_NUMBER;
                index_l2 = (i-1) / MAX_NUMBER;
                index_a1 = i % MAX_NUMBER;
                index_a2 = (i-1) % MAX_NUMBER;
                list.get(index_l1).set(index_a1, list.get(index_l2).get(index_a2));
                i++;
            }
        }
    }

    public void remove(int index) {
        int num1 = index/MAX_NUMBER;
        int num2 = index%MAX_NUMBER;
        list.get(num1).remove(num2);
        size--;
        shift(index, 0);
    }

    public int getSize() {
        return size;
    }
}
