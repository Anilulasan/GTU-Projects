
public class HashtableCoal<K, V> implements KWHashMap<K, V> {

    private static class Entry<K, V> {
        /**
         * The key
         */
        private final K key;
        /**
         * The value
         */
        private V value;
        /**
         * The value
         */
        private Integer next;

        /**
         * Creates a new key‐value pair. @param key The key
         *
         * @param value The value
         */
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
            this.next = null;
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

        //Points to the table[next] with holding index of next element.
        public void setNext(int next) {
            this.next = next;
        }

        //Returns next element's index.
        public Integer getNext() {
            return next;
        }

        @Override
        public String toString() {
            return "Key-> "+key+", Value-> "+value+"\n";
        }
    }


    private Entry<K, V>[] table;
    private static final int START_CAPACITY = 101;
    private final double LOAD_THRESHOLD = 0.75;
    private int numKeys;

    public HashtableCoal() {
        table = new Entry[START_CAPACITY];
    }

    private int find(Object key) {
        int index = key.hashCode()%table.length;
        if (index < 0)
            index += table.length;

        int probeNum = 0, startIndex = index, hold_index= 0;
        boolean collision = false;
        while (table[index] != null && !key.equals(table[index].getKey())) {
            probeNum++;
            collision = true;
            //Holding index to set the 'next' to the found index of the entry.
            if (table[index].getNext() == null) {
                hold_index = index;
                index = (startIndex+ probeNum*probeNum) % table.length;
            }
            else {
                index = table[index].getNext();
            }

        }
        if (collision)
            table[hold_index].setNext(index);
        return index;
    }

    private void rehash() {
        Entry<K, V>[] oldTable = table;
        table = new Entry[2* oldTable.length +1];
        numKeys = 0;
        for (int i = 0; i < oldTable.length; i++) {
            if (oldTable[i] != null)
                put(oldTable[i].getKey(), oldTable[i].getValue());
        }
    }

    @Override
    public V get(Object key) {
        int index = find(key);
        if (table[index] != null)
            return table[index].getValue();
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
        int index = find(key);
        if (table[index] == null) {
            table[index] = new Entry<>(key, value);
            numKeys++;
            if (numKeys/ table.length > LOAD_THRESHOLD)
                rehash();
            return null;
        }
        V oldVal = table[index].getValue();
        table[index].setValue(value);
        return oldVal;
    }

    @Override
    public V remove(Object key) {
        int index = find(key);
        if (table[index] == null)
            return null;
        V deletedVal = table[index].getValue();
        numKeys--;
        //If deleted key has not next entry, just set the table[index] to null.
        if (table[index].getNext() == null)
            table[index] = null;
        //If deleted key has next entry, replace it with deleted item.
        else {
            int nextIndex = table[index].getNext();
            table[index] = table[nextIndex];
            table[nextIndex] = null;
        }
        return deletedVal;
    }

    @Override
    public int size() {
        return numKeys;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < table.length; i++) {
            if (table[i] != null)
                sb.append(table[i].toString());
        }
        return sb.toString();
    }
}
