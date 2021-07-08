public class BTree<E extends Comparable<E>> {// Nested class

    private static class Node<E> {
        // Data Fields
        private int size = 0;

        private E[] data;

        private Node<E>[] child;

        @SuppressWarnings("unchecked")
        public Node(int order) {
            data = (E[]) new Comparable[order - 1];
            child = (Node<E>[]) new Node[order];
            size = 0;
        }

    }

    private Node<E> root = null;
    private int order;
    private Node<E> newChild;
    private E newParent;

    public BTree(int order) {
        this.order = order;
        root = null;
    }

    public boolean insert(E item) {
        if (order == 0) throw new IllegalStateException("Must set order first");

        if (root == null) {
            root = new Node<E>(order);
            root.data[0] = item;
            root.size = 1;
            return true;
        }
        newChild = null;
        boolean result = insert(root, item);
        if (newChild != null) {
            Node<E> newRoot = new Node<E>(order);
            newRoot.child[0] = root;
            newRoot.child[1] = newChild;
            newRoot.data[0] = newParent;
            newRoot.size = 1;
            root = newRoot;
        }
        return result;
    }

    private boolean insert(Node<E> root, E item) {
        int index = binarySearch(item, root.data, 0, root.size);
        if (index != root.size && item.compareTo(root.data[index]) == 0) {
            return false;
        }
        if (root.child[index] == null) {
            if (root.size < order - 1) {
                insertIntoNode(root, index, item, null);
                newChild = null;
            } else {
                splitNode(root, index, item, null);
            }
            return true;
        } else {
            boolean result = insert(root.child[index], item);
            if (newChild != null) {
                if (root.size < order - 1) {
                    insertIntoNode(root, index, newParent, newChild);
                    newChild = null;
                } else {
                    splitNode(root, index, newParent, newChild);
                }
            }
            return result;
        }
    }

    private void insertIntoNode(Node<E> node, int index, E obj, Node<E> child) {
        for (int i = node.size; i > index; i--) {
            node.data[i] = node.data[i - 1];
            node.child[i + 1] = node.child[i];
        }
        node.data[index] = obj;
        node.child[index + 1] = child;
        node.size++;
    }

    private void splitNode(BTree.Node<E> node, int index, E item, BTree.Node<E> child) {

        newChild = new Node<E>(order);

        int numToMove = (order - 1) - ((order - 1) / 2);

        if (index > (order - 1) / 2) numToMove--;


        System.arraycopy(node.data, order - numToMove - 1, newChild.data, 0, numToMove);
        System.arraycopy(node.child, order - numToMove, newChild.child, 1, numToMove);

        node.size = order - numToMove - 1;
        newChild.size = numToMove;

        if (index == ((order - 1) / 2)) {
            newParent = item;
            newChild.child[0] = child;

        } else {
            if (index < ((order - 1) / 2)) insertIntoNode(node, index, item, child);

            else insertIntoNode(newChild, index - ((order - 1) / 2) - 1, item, child);

            newParent = node.data[node.size - 1];

            newChild.child[0] = node.child[node.size];
            node.size--;
        }

        for (int i = node.size; i < node.data.length; i++) {
            node.data[i] = null;
            node.child[i + 1] = null;
        }
    }

    public int binarySearch(E target, E[] items, int first, int last) {


        if (target.compareTo(items[last - 1]) > 0)
            return last;

        int start = first;
        int end = last;

        while (start <= end) {
            int middle = (start + end) / 2;

            int compResult = target.compareTo(items[middle]);
            if (compResult < 0)
                end = middle - 1;

            if (compResult > 0)
                start = middle + 1;

            if (compResult == 0)
                return middle;
        }

        for (int i = first; i < last; i++)
            if (target.compareTo(items[i]) < 0) return i;

        return last;
    }


}