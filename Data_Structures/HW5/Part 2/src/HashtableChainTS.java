import java.util.*;

public class HashtableChainTS<K extends Comparable<K>, V> implements KWHashMap<K, V> {

    private static class Entry<K extends Comparable<K>, V> implements Comparable<Entry<K, V>>{
        /**
         * The key
         */
        private final K key;
        /**
         * The value
         */
        private V value;

        /**
         * Creates a new key‐value pair. @param key The key
         *
         * @param value The value
         */
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        /**
         * Retrieves the key. @return The key
         */
        public K getKey() {
            return key;
        }

        /**
         * Retrieves the value. @return The value
         */
        public V getValue() {
            return value;
        }

        /**
         * Sets the value.
         *
         * @param val The new value @return The old value
         */
        public V setValue(V val) {
            V oldVal = value;
            value = val;
            return oldVal;
        }

        public int compareTo(Entry<K, V> e1) {
            return this.key.compareTo(e1.key);
        }

        @Override
        public String toString() {
            return "Key-> "+key+", Value-> "+value+"\n";
        }
    }

    private TreeSet<Entry<K, V>>[] table;
    private int numKeys = 0;
    private static final int CAPACITY = 101;
    private static final double LOAD_THRESHOLD = 3.8;

    public HashtableChainTS() {
        table = new TreeSet[CAPACITY];
    }

    private void rehash() {
        TreeSet<Entry<K, V>>[] oldTable = table;
        table = new TreeSet[oldTable.length*2 +1];

        numKeys = 0;
        for (int i = 0; i < oldTable.length; i++) {
            if (oldTable[i] != null) {
                for (int j = 0; j < oldTable[i].size(); j++) {
                    Entry<K, V> e = oldTable[i].pollFirst();
                    put(e.getKey(), e.getValue());
                }
            }
        }

    }

    @Override
    public V get(Object key) {
        int index = key.hashCode() % table.length;
        if (index < 0)
            index += table.length;

        if (table[index] == null)
            return null;

        for (Entry<K, V> nextItem : table[index])
            if (nextItem.getKey().equals(key))
                return nextItem.getValue();
        return null;
    }

    @Override
    public boolean isEmpty() {
        if (numKeys == 0)
            return true;
        return false;
    }

    @Override
    public V put(K key, V value) {
        int index = key.hashCode() % table.length;
        if (index < 0)
            index += table.length;

        if (table[index] == null)
            table[index] = new TreeSet<Entry<K, V>>();


        for (Entry<K, V> nextItem : table[index])
            if (nextItem.getKey().equals(key)) {
                V oldVal = nextItem.getValue();
                nextItem.setValue(value);
                return oldVal;
            }


        table[index].add(new Entry<>(key, value));
        numKeys++;
        if (numKeys > LOAD_THRESHOLD* table.length)
            rehash();
        return null;
    }

    @Override
    public V remove(Object key) {
        int index = key.hashCode() % table.length;
        if (index < 0)
            index += table.length;

        if (table[index] == null)
            return null;

        for (Entry<K, V> nextItem : table[index])
            if (nextItem.getKey().equals(key)) {
                V oldVal = nextItem.getValue();
                table[index].remove(nextItem);
                numKeys--;
                if (table[index].size() == 0)
                    table[index] = null;
                return oldVal;
            }

        return null;
    }

    @Override
    public int size() {
        return numKeys;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < table.length; i++) {
            if (table[i] != null) {
                for (int j = 0; j < table[i].size(); j++) {
                    sb.append(table[i].pollFirst().toString());
                }
            }
        }
        return sb.toString();
    }
}