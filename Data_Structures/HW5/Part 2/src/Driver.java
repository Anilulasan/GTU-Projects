import java.time.Duration;
import java.time.Instant;

public class Driver {
    public static void main(String[] args)  {
        test();
    }


    /*Test methods.
    // They will take @param as Hashtable classes with upcasting.
    //They @return the time they spent to do these operations*/
    public static Duration testSmall(KWHashMap<Integer, Integer> hTable) {
        Instant start = Instant.now();
        System.out.println("----------------Inserting 20 entries to the table--------------------");

        for (int i = 0; i < 20; i++) {
            hTable.put(i*2, i*5);
        }
        System.out.println(hTable);
        //Remove some elements from table.
        System.out.println("----------------Removing some entries from the table--------------------");
        for (int i = 8; i < 11; i++) {
            hTable.remove(i*2);
        }
        System.out.println(hTable);
        //Put some entries that has same key with some elements in the table.
        System.out.println("----------------Inserting some entries that has existent keys to the table--------------------");
        for (int i = 3; i < 6; i++) {
            hTable.put(i*2, i*3);
        }
        System.out.println(hTable);
        //Try to access non-existing keys.
        for (int i = 0; i < 3; i++) {
            hTable.get(i*(-1) -1);
        }
        //Access existing keys.
        for (int i = 0; i < 3; i++) {
            hTable.get(i*2);
        }

        //Try to remove non-existing keys
        for (int i = 0; i < 3; i++) {
            hTable.remove(i*(-1) -1);
        }
        Instant end = Instant.now();
        return Duration.between(start, end);
    }

    public static Duration testMedium(KWHashMap<Integer, Integer> hTable) {
        Instant start = Instant.now();


        for (int i = 0; i < 100; i++) {
            hTable.put(i*2, i*5);
        }
        //Remove 10 elements from table.
        for (int i = 20; i < 30; i++) {
            hTable.remove(i*2);
        }
        //Put some entries that has same key with some elements in the table.
        for (int i = 60; i < 70; i++) {
            hTable.put(i*2, i*3);
        }
        //Try to access non-existing keys.
        for (int i = 0; i < 5; i++) {
            hTable.get(i*(-1) -1);
        }
        //Access existing keys.
        for (int i = 0; i < 5; i++) {
            hTable.get(i*2);
        }

        //Try to remove non-existing keys
        for (int i = 0; i < 8; i++) {
            hTable.remove(i*(-1) -1);
        }

        Instant end = Instant.now();
        return Duration.between(start, end);
    }

    public static Duration testLarge(KWHashMap<Integer, Integer> hTable) {
        Instant start = Instant.now();


        //Fill the table with 1000 entries.
        for (int i = 0; i < 1000; i++) {
            hTable.put(i*2, i*5);
        }
        //Remove 100 elements from table.
        for (int i = 80; i < 180; i++) {
            hTable.remove(i*2);
        }
        //Put some entries that has same key with some elements in the table.
        for (int i = 230; i < 330; i++) {
            hTable.put(i*2, i*3);
        }
        //Try to access non-existing keys.
        for (int i = 0; i < 50; i++) {
            hTable.get(i*(-1) -1);
        }
        //Access existing keys.
        for (int i = 0; i < 50; i++) {
            hTable.get(i*2);
        }

        //Try to remove non-existing keys
        for (int i = 0; i < 25; i++) {
            hTable.remove(i*(-1) -1);
        }


        Instant end = Instant.now();
        return Duration.between(start, end);
    }

    public static void test() {
        Duration[] timeLLTables = new Duration[3];
        Duration[] timeTSTables = new Duration[3];
        Duration[] timeCoalTables = new Duration[3];

        //Creating tables and putting them to test.
        System.out.println("--------------Test small Table for ChainLL------------------\n\n");
        HashtableChainLL<Integer, Integer> hTableLL0 = new HashtableChainLL<>();
        timeLLTables[0] = testSmall(hTableLL0);

        System.out.println("--------------Test medium Table for ChainLL------------------");
        HashtableChainLL<Integer, Integer> hTableLL1 = new HashtableChainLL<>();
        timeLLTables[1] = testMedium(hTableLL1);

        System.out.println("--------------Test large Table for ChainLL------------------");
        HashtableChainLL<Integer, Integer> hTableLL2 = new HashtableChainLL<>();
        timeLLTables[2] = testLarge(hTableLL2);

        System.out.println("--------------Test small Table for ChainTS------------------");
        HashtableChainTS<Integer, Integer> hTableTS0 = new HashtableChainTS<>();
        timeTSTables[0] = testSmall(hTableTS0);

        System.out.println("--------------Test medium Table for ChainTS------------------");
        HashtableChainTS<Integer, Integer> hTableTS1 = new HashtableChainTS<>();
        timeTSTables[1] = testMedium(hTableTS1);

        System.out.println("--------------Test large Table for ChainTS------------------");
        HashtableChainTS<Integer, Integer> hTableTS2 = new HashtableChainTS<>();
        timeTSTables[2] = testLarge(hTableTS2);

        System.out.println("--------------Test small Table for ChainCoal------------------");
        HashtableCoal<Integer, Integer> hTableC0 = new HashtableCoal<>();
        timeCoalTables[0] = testSmall(hTableC0);

        System.out.println("--------------Test medium Table for ChainCoal------------------");
        HashtableCoal<Integer, Integer> hTableC1 = new HashtableCoal<>();
        timeCoalTables[1] = testMedium(hTableC1);

        System.out.println("--------------Test large Table for ChainLL------------------\n\n\n\n\n");
        HashtableCoal<Integer, Integer> hTableC2 = new HashtableCoal<>();
        timeCoalTables[2] = testLarge(hTableC2);

        System.out.println("-----------Small tables---------------");
        System.out.println("HashTableChainLL------>"+timeLLTables[0]);
        System.out.println("HashTableChainTS------>"+timeTSTables[0]);
        System.out.println("HashTableCoalesced---->"+timeCoalTables[0]);

        System.out.println("-----------Medium tables---------------");
        System.out.println("HashTableChainLL------>"+timeLLTables[1]);
        System.out.println("HashTableChainTS------>"+timeTSTables[1]);
        System.out.println("HashTableCoalesced---->"+timeCoalTables[1]);

        System.out.println("-----------Large tables---------------");
        System.out.println("HashTableChainLL------>"+timeLLTables[0]);
        System.out.println("HashTableChainTS------>"+timeTSTables[1]);
        System.out.println("HashTableCoalesced---->"+timeCoalTables[2]);
    }
}

