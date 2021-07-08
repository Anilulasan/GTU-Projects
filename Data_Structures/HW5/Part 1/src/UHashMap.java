import java.util.*;

public class UHashMap<K, V> extends HashMap<K, V> {

    private ArrayList<K> keys;

    public UHashMap() {
        super();
        keys = new ArrayList<K>();
    }

    private class MapIterator implements GTUIterator<K>{
        private int index = 0;
        private int iterated_count = 0;

        public MapIterator() {
            Random rand = new Random();
            index = rand.nextInt(keys.size());
        }

        public MapIterator(K key) throws NoSuchElementException{
            index = keys.indexOf(key);
            if (index == -1)
                throw new NoSuchElementException();
        }

        @Override
        public boolean hasNext() {
            if (iterated_count < keys.size())
                return true;
            return false;
        }

        @Override
        public K next() {
            //If there are no not-iterated key in the map,
            //Starts from first index, sets iterated count to 0 and goes on.
            if (iterated_count == keys.size()) {
                iterated_count = 0;
                index = 0;
            }

            iterated_count++;
            //To iterate circular, index is set to 0 when comes to end of the array.
            if (index == keys.size())
                index = 0;
            return keys.get(index++);
        }

        public K prev() {
            if (index == -1)
                index = keys.size()-1;
            return keys.get(index--);
        }

    }

    public GTUIterator<K> iterator(K key) {
        return new MapIterator(key);
    }

    public GTUIterator<K> iterator() {
        return new MapIterator();
    }

    @Override
    public V put(K key, V value) {
        keys.add(key);
        return super.put(key, value);
    }
}
