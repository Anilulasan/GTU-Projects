import java.time.Duration;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.Random;
import java.time.Instant;

public class Driver {
    private static ArrayList<Integer> randoms;
    private static ArrayList<RedBlackTree<Integer>> rbTrees = new ArrayList<>();
    private static ArrayList<BinarySearchTree<Integer>> bsTrees = new ArrayList<>();
    private static ArrayList<BTree<Integer>> bTrees = new ArrayList<>();
    private static ArrayList<SkipList<Integer>> skipLists = new ArrayList<>();
    private static ArrayList<TwoThreeTree<Integer>> ttTrees = new ArrayList<>();

    public static void main(String[] args) {
        randoms = new ArrayList<>();
        test();
    }

    public static void test() {
        //Durations for every data structure and every size averages.
        Duration[] tens = new Duration[5];
        Duration[] twenties = new Duration[5];
        Duration[] fourties = new Duration[5];
        Duration[] eighties = new Duration[5];

        fillThenMeasure(10000, tens);
        fillThenMeasure(20000, twenties);
        fillThenMeasure(40000, fourties);
        fillThenMeasure(80000, eighties);

        System.out.println("=================Test 10000==================");
        printRes(10000, tens);
        System.out.println("=================Test 10000==================\n\n\n");
        System.out.println("=================Test 20000==================");
        printRes(20000, twenties);
        System.out.println("=================Test 20000==================\n\n\n");
        System.out.println("=================Test 40000==================");
        printRes(40000, fourties);
        System.out.println("=================Test 40000==================\n\n\n");
        System.out.println("=================Test 80000==================");
        printRes(80000, eighties);
        System.out.println("=================Test 80000==================\n\n\n");
    }

    public static void fillThenMeasure(int count, Duration[] durs) {
        BinarySearchTree<Integer> bst = new BinarySearchTree<>();
        BTree<Integer> bt = new BTree<>(3);
        RedBlackTree<Integer> rbt = new RedBlackTree<>();
        TwoThreeTree<Integer> ttt = new TwoThreeTree<>();
        SkipList<Integer> sl = new SkipList<>();

        Instant start, end;
        for (int i = 0; i < 10; i++) {
            createRandom(count);
            for (int j = 0; j < count; j++) {
                bst.add(randoms.get(j));
                bt.insert(randoms.get(j));
                rbt.add(randoms.get(j));
                ttt.add(randoms.get(j));
                sl.add(randoms.get(j));
            }
            randoms.clear();
            createRandom(100);
            start = Instant.now();
            for (int j = 0; j < 100; j++) {
                bst.add(randoms.get(j));
            }
            end = Instant.now();
            if (i == 0)
                durs[0] = Duration.between(start, end);
            else
                durs[0] = durs[0].plus(Duration.between(start, end));

            start = Instant.now();
            for (int j = 0; j < 100; j++) {
                bt.insert(randoms.get(j));
            }
            end = Instant.now();
            if (i == 0)
                durs[1] = Duration.between(start, end);
            else
                durs[1] = durs[0].plus(Duration.between(start, end));

            start = Instant.now();
            for (int j = 0; j < 100; j++) {
                rbt.add(randoms.get(j));
            }
            end = Instant.now();
            if (i == 0)
                durs[2] = Duration.between(start, end);
            else
                durs[2] = durs[0].plus(Duration.between(start, end));

            start = Instant.now();
            for (int j = 0; j < 100; j++) {
                ttt.add(randoms.get(j));
            }
            end = Instant.now();
            if (i == 0)
                durs[3] = Duration.between(start, end);
            else
                durs[3] = durs[0].plus(Duration.between(start, end));

            start = Instant.now();
            for (int j = 0; j < 100; j++) {
                sl.add(randoms.get(j));
            }
            end = Instant.now();
            if (i == 0)
                durs[4] = Duration.between(start, end);
            else
                durs[4] = durs[0].plus(Duration.between(start, end));
        }

        for (int i = 0; i < 5; i++) {
            durs[i] = durs[i].dividedBy(10);
        }
    }

    private static void printRes(int size, Duration[] durations) {

        System.out.println("BST average for size:"+size+" = "+durations[0]);
        System.out.println("Btree average for size:"+size+" = "+durations[1]);
        System.out.println("R-BTree average for size:"+size+" = "+durations[2]);
        System.out.println("2-3Tree average for size:"+size+" = "+durations[3]);
        System.out.println("SL average for size:"+size+" = "+durations[4]);
    }

    //@param count, number of variables generated.
    private static void createRandom(int count) {
        LinkedHashSet<Integer> hold= new LinkedHashSet<>();
        Random rand = new Random();
        for (int i = 0; i < count; i++) {
            int random = rand.nextInt(1000000);
            while (!hold.add(random)) {
                random = rand.nextInt(1000000);
            }
            randoms.add(random);
        }
    }
}
