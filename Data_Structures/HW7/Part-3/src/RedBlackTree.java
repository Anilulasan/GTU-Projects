public class RedBlackTree<E extends Comparable<E>>
        extends BinarySearchTreeWithRotate<E> {
    /**
     * Nested class to represent a Red‐Black node.
     */
    private static class RedBlackNode<E> extends Node<E> {
        private boolean isRed;
        // Constructor

        public RedBlackNode(E item) {
            super(item);
            isRed = true;
        }
        // Methods

        @Override
        public String toString() {
            if (isRed) {
                return "Red : " + super.toString();
            } else {
                return "Black: " + super.toString();
            }
        }
    }

    public boolean add(E item) {
        if (root == null) {
            root = new RedBlackNode<>(item);
            ((RedBlackNode<E>) root).isRed = false; // root is black.
            return true;
        } else {
            root = add((RedBlackNode<E>) root, item);
            ((RedBlackNode<E>) root).isRed = false; // root is always black.
            return addReturn;
        }
    }

    private BinaryTree.Node<E> add(RedBlackTree.RedBlackNode<E> localRoot, E item) {
        if (item.compareTo(localRoot.data) == 0) {
            // item already in the tree.
            addReturn = false;
            return localRoot;
        }
        else if (item.compareTo(localRoot.data) < 0) {
            // item < localRoot.data.
            if (localRoot.left == null) {
                // Create new left child.
                localRoot.left = new RedBlackNode<>(item);
                addReturn = true;
                return localRoot;
            }
            else { // Need to search.
                // Check for two red children, swap colors if found.
                moveBlackDown(localRoot);
                // Recursively add on the left.
                localRoot.left = add((RedBlackNode<E>) localRoot.left, item);
                if (((RedBlackNode<E>) localRoot.left).isRed) {
                    if (localRoot.left.left != null && ((RedBlackNode<E>) localRoot.left.left).isRed) {
                        // Single rotation is necessary.
                        ((RedBlackNode<E>) localRoot.left).isRed = false;
                        localRoot.isRed = true;
                        return rotateRight(localRoot);
                    }
                    else if (localRoot.left.right != null && ((RedBlackNode<E>)
                            localRoot.left.right).isRed) {
                        // Left‐right grandchild is also red.
                        // Double rotation is necessary.
                        localRoot.left = rotateLeft(localRoot.left);
                        ((RedBlackNode<E>) localRoot.left).isRed = false;
                        localRoot.isRed = true;
                        return rotateRight(localRoot);
                    }
                }
                return localRoot;
            }
        }
        //Implemented last statement. Just done the opposite of item<localroot.data
        else {
            //item is greater than localRoot.data
            if (localRoot.right == null) {
                //Create new right child
                localRoot.right = new RedBlackNode<E>(item);
                addReturn = true;
                return localRoot;
            } else { //Need to search
                //Check for two red children, swap colors if found.
                moveBlackDown(localRoot);
                //Recursively add on the right.
                localRoot.right = add((RedBlackNode<E>) localRoot.right, item);
                if (((RedBlackNode<E>) localRoot.right).isRed) {
                    if (localRoot.right.right != null && ((RedBlackNode<E>) localRoot.right.right).isRed) {
                    //Single rotation is necessary.
                        ((RedBlackNode<E>) localRoot.right).isRed = false;
                        localRoot.isRed = true;
                        return rotateLeft(localRoot);
                    }
                    else if (localRoot.right.left != null
                        && ((RedBlackNode<E>) localRoot.right.left).isRed) {
                    //Right-left grand-child is also red.
                    //Double rotation is necessary.
                    localRoot.right = rotateRight(localRoot.right);
                    ((RedBlackNode<E>) localRoot.right).isRed = false;
                    localRoot.isRed = true;
                    return rotateLeft(localRoot);
                }
            }
            return localRoot;
            }
        }
    }


    private void moveBlackDown(RedBlackTree.RedBlackNode<E> localRoot) {
        if(localRoot.left != null && localRoot.right != null){ //If a child is null, it is black
            if(((RedBlackNode<E>) localRoot.left).isRed
                    && ((RedBlackNode<E>) localRoot.right).isRed){ //if both children are red, swap colors
                ((RedBlackNode<E>) localRoot.left).isRed = false;
                ((RedBlackNode<E>) localRoot.right).isRed = false;
                localRoot.isRed = true;
            }
        }
    }

}

