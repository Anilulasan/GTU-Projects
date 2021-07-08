import java.util.Arrays;
import java.util.Random;
public class SkipList<E extends Comparable<E>> {
    private static class SLNode<E extends Comparable<E>> {
        private SkipList.SLNode<E>[] links;

        private E[] elements;

        private int USED;

        private int capacity;

        /**
         * Create a node of level m
         * @param m The level of the node
         * @param data The data to be stored
         */
        @SuppressWarnings("unchecked")
        public SLNode(int m, E data, int max_capa) {
            links = (SLNode<E>[]) new SLNode[m];
            this.USED = 0;
            this.capacity = max_capa;

            elements = (E[]) new Comparable[capacity];
            elements[USED++] = data;
        }

        public boolean add(E item) {
            if(USED == capacity)
                return false;

            if(item.compareTo(elements[USED-1]) < 0) {
                elements[USED++] = item;
                return true;
            }

            for(int i = 0 ; i < USED ; ++i) {
                if(item.compareTo(elements[USED-1]) > 0) {
                    for(int j = USED ; j >= i ; --j)
                        elements[j] = elements[j-1];

                    elements[i] = item;
                    ++USED;
                    return true;
                }
            }

            return false;
        }

        public int getUSED() {
            return USED;
        }

        public E get(int i) {
            if(i < 0 && i >= USED) return null;

            return elements[i];
        }

        @Override
        public String toString() {

            StringBuilder sb = new StringBuilder();

            sb.append("[ ");
            for(int i = 0 ; i < USED ; ++i) {

                sb.append(elements[i].toString());

                if(i != (USED-1) )
                    sb.append(", ");
            }
            sb.append(" ]");
            sb.append(" /");
            sb.append(links.length);
            sb.append("/ ");

            return sb.toString();
        }

    }

    /**
     *
     * Head of the skip-list
     *
     */
    public SkipList.SLNode<E> head;

    /**
     * Size of the skip list
     *
     */
    private int size;

    /**
     * The maximum level of the skip-list
     *
     */
    private int maxLevel;

    /**
     * Smallest power of 2 that is greater than the current skip-list size
     *
     */
    private int maxCap;

    /**
     * Natural log of 2
     *
     */
    private static final double LOG2 =  Math.log(2.0);

    /**
     * Minimum possible integer value for the head
     *
     */
    private static final int MIN =  Integer.MIN_VALUE;

    /**
     * Random number generator
     *
     */
    private Random rand =  new Random();

    private int max_arr;

    private int min_arr;

    @SuppressWarnings({ "unchecked", "rawtypes" })
    public SkipList() {
        size = 0;
        maxLevel = 0;
        maxCap = computeMaxCap(maxLevel);
        this.max_arr = 1;
        this.min_arr = 0;

        head = new SLNode(maxLevel, MIN, max_arr);
    }

    @SuppressWarnings({ "unchecked", "rawtypes" })
    public SkipList(int min_arr, int max_arr) {
        size = 0;
        maxLevel = 0;
        maxCap = computeMaxCap(maxLevel);
        this.max_arr = max_arr;
        this.min_arr = min_arr;

        head = new SLNode(maxLevel, MIN, max_arr);
    }

    /**
     * Search for an item in the list
     * @param target The item being sought
     * @return An SLNode array which references the predecessors of the target at each level.
     */
    @SuppressWarnings("unchecked")
    private SkipList.SLNode<E>[] search(E target) {

        SLNode<E>[] pred = (SLNode<E>[]) new SLNode[maxLevel];
        SLNode<E> current = head;

        for(int i = current.links.length - 1; i >= 0; i--) {

            while(current.links[i] != null && compareNode_target(current.links[i].elements, target))
                current = current.links[i];
            pred[i] = current;
        }

        return pred;
    }

    private boolean compareNode_target(E[] elements, E target) {
        for (E element : elements)
            if (element != null)
                if (element.compareTo(target) < 0)
                    return true;
        return false;
    }

    /**
     * Find an object in the skip-list
     * @param target The item being sought
     * @return A reference to the object in the skip-list that matches
     * 		   the target. If not found, null is returned
     */
    public E find(E target) {
        SLNode<E>[] pred = search(target);

        if(pred[0].links != null) return isFound(pred[0].links[0].elements, target);
        else return null;
    }

    private E isFound(E[] elements, E target) {
        for(E element : elements)
            if(element != null)
                if(element.equals(target))
                    return element;
        return null;
    }

    /**
     * Inserts the given item
     * @param item The item to add
     * @return true as the item is added
     */
    public boolean add(E item) {
        size++;
        SLNode<E>[] pred = search(item);

        if(pred.length >  0 && pred[0].links.length > 0 && pred[0].links[0] != null)
            if(pred[0].links[0].getUSED() < max_arr)
                return pred[0].links[0].add(item);

            else if(pred.length > 0 && pred[0] != head && !(pred[0].links.length > 0 && pred[0].links[0] != null))
                if(pred[0].links[0].getUSED() < max_arr)
                    return pred[0].add(item);

                else {
                    if(size > maxCap) {
                        maxLevel++;
                        maxCap = computeMaxCap(maxLevel);
                        head.links = Arrays.copyOf(head.links, maxLevel);
                        pred = Arrays.copyOf(pred, maxLevel);
                        pred[maxLevel - 1] = head;
                    }

                    SLNode<E> newNode = new SLNode<E>(logRandom(), item, max_arr);

                    if(pred.length > 0 && pred[0].links.length > 0  && pred[0].links[0] != null) {
                        SLNode<E> current = pred[0].links[0];
                        if(current.getUSED() > 0 && current.get(0) != null && current.get(0).compareTo(item) < 0)
                            return current.add(item);
                        else
                            return newNode.add(item);
                    }
                    else newNode.add(item);

                    for(int i = 0; i < newNode.links.length; i++) {
                        newNode.links[i] = pred[i].links[i];
                        pred[i].links[i] = newNode;
                    }
                }

        return true;
    }


    private int logRandom() {
        int r = rand.nextInt(maxCap);
        int k = (int) (Math.log(r + 1) / LOG2);
        if(k > maxLevel - 1)
            k = maxLevel - 1;
        return maxLevel - k;
    }

    /**
     * Recompute the max cap
     * @param level
     * @return
     */
    private int computeMaxCap(int level) {
        return (int) Math.pow(2, level) - 1;
    }

    @SuppressWarnings("rawtypes")
    public String toString() {
        if(size == 0)
            return "Empty";
        StringBuilder sc = new StringBuilder();
        SLNode itr = head;
        sc.append("Head: ");
        sc.append(maxLevel);

        int lineMaker = 0;
        if(itr.links.length > 0) {
            while(itr.links[0] != null){
                itr = itr.links[0];
                sc.append(" --> ");
                sc.append(itr.toString());
                lineMaker++;
                if(lineMaker == 10){
                    sc.append("\n");
                    lineMaker = 0;
                }
            }
        }

        return sc.toString();
    }

}