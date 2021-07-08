public class BinarySearchTree<E extends Comparable<E>> extends BinaryTree<E> {

    protected boolean addReturn;
    protected E deleteReturn;
    public BinarySearchTree() {
        root = null;
    }

    public BinarySearchTree(Node<E> root) {
        this.root = root;
    }

    public BinarySearchTree(E data, BinarySearchTree<E> leftTree, BinarySearchTree<E> rightTree) {
        root = new Node<E>(data);
        if (leftTree == null)
            root.left = null;
        else
            root.left = leftTree.root;
        if (rightTree == null)
            root.right = null;
        else
            root.right = rightTree.root;

    }

    public E find(E target) {
        return find(root, target);
    }

    private E find(Node<E> localRoot, E target) {
        if (localRoot == null)
            return null;
        else if(target.compareTo(localRoot.data) < 0)
            return find(localRoot.left, target);
        else if (target.compareTo(localRoot.data) > 0)
            return find(localRoot.right, target);
        else
            return target;
    }

    public boolean add(E data) {
        root = add(root, data);
        return addReturn;
    }

    private Node<E> add(Node<E> node, E item) {
        if (node == null) {
            addReturn = true;
            return new Node<>(item);
        }
        else if (item.compareTo(node.data) < 0) {
            node.left = add(node.left, item);
            return node;
        }
        else if(item.compareTo(node.data) > 0) {
            node.right = add(node.right, item);
            return node;
        }
        else {
            addReturn = false;
            return node;
        }
    }


}
