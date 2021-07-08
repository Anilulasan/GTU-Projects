import java.util.HashMap;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class Driver {
    public static void main(String[] args) {
        UHashMap<Integer, Integer> hMap = new UHashMap();
        System.out.println("-----------------------------MapIterator Test---------------------------------\n\n");
        System.out.println("----------------------Adding some elements to the hashmap(int-int)---------------------\n");
        for (int i = 0; i < 25; i++)
            hMap.put(i, 100 - i);


        System.out.println(hMap);
        System.out.println("--------------25 key&values are added---------------\n\n");
        System.out.println("--------------Create the iterator with non-existent key '-1'---------------");
        GTUIterator iter;
        try {
            iter = hMap.iterator(-1);
        }catch (NoSuchElementException ex) {
            System.out.println("Exception occured: Key is not found in the hashmap...\n\n");
        }
        System.out.println("--------------Create the iterator with an existent key '5'---------------");
        iter = hMap.iterator(5);
        System.out.println("--------------Iterate with next() method 30 times using hasNext()---------------");
        while (iter.hasNext())
            System.out.println("key->"+iter.next());

        System.out.println("--------------Iterate with next() method 30 times---------------");
        for (int i = 0; i < 30; i++)
            System.out.println("key->"+iter.next());

        System.out.println("--------------Iterate with prev() method 30 times---------------");
        for (int i = 0; i < 30; i++)
            System.out.println("key->"+iter.prev());

        iter = hMap.iterator();
        System.out.println("--------------Create the iterator with no parameter---------------");
        System.out.println("--------------Iterate with next() method 30 times---------------");
        for (int i = 0; i < 30; i++)
            System.out.println("key->"+iter.next());

    }
}
