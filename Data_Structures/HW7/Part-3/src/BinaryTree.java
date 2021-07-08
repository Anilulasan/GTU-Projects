import java.util.Scanner;

public class BinaryTree<E> {
    protected Node<E> root;

    protected static class Node<E> {
        protected Node<E> right;
        protected Node<E> left;
        protected E data;

        public Node(E data_) {
            this.data = data_;
            left = null;
            right = null;
        }
    }

    public BinaryTree() {
        root = null;
    }

    protected BinaryTree(Node<E> root_) {
        root = root_;
    }

    public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree) {
        root = new Node<E>(data);
        if (leftTree != null)
            root.left = leftTree.root;
        else
            root.left = null;

        if (rightTree != null)
            root.left = rightTree.root;
        else
            root.left = null;

    }

    public BinaryTree<E> getLeftSubtree() {
        BinaryTree<E> res = new BinaryTree<>();
        if (root != null && root.left != null)
            res.root = this.root.left;
        else
            return null;
        return res;
    }

    public BinaryTree<E> getRightSubtree() {
        BinaryTree<E> res = new BinaryTree<>();
        res.root = this.root.right;
        return res;
    }

    public E getData() {
        if (root != null)
            return root.data;
        return null;
    }

    public boolean isLeaf() {
        return (root != null && root.left == null && root.right == null);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root, 1, sb);
        return sb.toString();
    }

    private void preOrderTraverse(Node<E> node, int depth, StringBuilder sb) {
        for (int i = 0; i < depth; i++)
            sb.append("  ");
        if (node == null) {
            sb.append("null\n");
        }
        else {
            sb.append(node.data);
            sb.append("\n");
            preOrderTraverse(node.left, depth+1, sb);
            preOrderTraverse(node.right, depth+1, sb);
        }
    }

    public static BinaryTree<String> readBinaryTree(Scanner scan) {
        String data = scan.next();
        if (data.equals("null"))
            return null;

        else {
            BinaryTree<String> leftTree = readBinaryTree(scan);
            BinaryTree<String> rightTree = readBinaryTree(scan);
            return new BinaryTree<String>(data, leftTree, rightTree);
        }
    }
}
