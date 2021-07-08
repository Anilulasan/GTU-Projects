public class Driver {
    public static void main(String[] args) {
        BinarySearchTree<Integer> tree = new BinarySearchTree<>();

        for (int i = 0; i < 15; i++) {
            if (i % 2 == 0)
                tree.add(i*2);
            else
                tree.add(i);
        }

        System.out.println(tree.toString());
        System.out.println("==============Test isAVL Method==================");
        System.out.println(isAVL(tree));

        System.out.println("==============Test isRedBlack Method==================");
        System.out.println(isRedBlack(tree));
        System.out.println("\n\n\n");
        tree = null;
        tree = new BinarySearchTree<>();
        tree.add(8);
        for (int i = 0; i < 15; i++) {
            tree.add(i);
        }
        System.out.println(tree.toString());
        System.out.println("==============Test isAVL Method==================");
        System.out.println(isAVL(tree));

        System.out.println("==============Test isRedBlack Method==================");
        System.out.println(isRedBlack(tree));

    }

    private static boolean isAVL(BinarySearchTree tree) {
        int bal = tree.Balance();
        if (bal <= 1 && bal >= -1)
            return true;
        return false;
    }

    private static boolean isRedBlack(BinarySearchTree tree) {
        return tree.isRed();
    }
}
