import java.util.*;
public class KWLinkedList<E> {
    private Node<E> head = null;
    private Node<E> tail = null;
    private int size = 0;

    private static class Node<E> {
        // Data Fields
        /** The reference to the data. */ private E data;
        /** The reference to the next node. */ private Node<E> next;
        /** The reference to the previous node. */private Node<E> prev;
        // Constructors
        /** Creates a new node with a null next field.
         @param dataItem The data stored */
        private Node(E dataItem) {
            data = dataItem;
            next = null;
            prev = null;
        }
        /** Creates a new node that references another node. @param dataItem The data stored
         @param nodeRef The node referenced by new node
         */
        private Node(E dataItem, Node<E> nodeRef) {
            data = dataItem;
            next = nodeRef;
        }
}

    private class KWListIter implements ListIterator<E> {
        /**
         * A reference to the next item.
         */
        private Node<E> nextItem;
        /**
         * A reference to the last item returned.
         */
        private Node<E> lastItemReturned;
        /**
         * The index of the current item.
         */
        private int index = 0;

        public KWListIter(int i) {
            // Validate i parameter.
            if (i < 0 || i > size) {
                throw new IndexOutOfBoundsException("Invalid index " + i);
            }
            lastItemReturned = null; // No item returned yet. // Special case of last item.
            if (i == size) {
                index = size;
                nextItem = null;
            } else { // Start at the beginning
                nextItem = head;
                for (index = 0; index < i; index++) {
                    nextItem = nextItem.next;
                }
            }
        }

        public boolean hasNext() {
            return nextItem != null;
        }

        public E next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            lastItemReturned = nextItem;
            nextItem = nextItem.next;
            index++;
            return lastItemReturned.data;
        }

        public boolean hasPrevious() {
            return (nextItem == null && size != 0) || nextItem.prev != null;
        }

        public E previous() {
            if (!hasPrevious()) {
                throw new NoSuchElementException();
            }
            if (nextItem == null) { // Iterator is past the last element nextItem = tail;
            }
            else {
                nextItem = nextItem.prev;
            }
            lastItemReturned = nextItem;
            index--;
            return lastItemReturned.data;
        }

        @Override
        public int nextIndex() {
            if (nextItem == null)
                return size;

            return index+1;
        }

        @Override
        public int previousIndex() {
            if (lastItemReturned == null)
                return -1;
            return index-1;
        }

        @Override
        public void remove() {
            lastItemReturned = nextItem.prev;
            if (size == 0) {
                throw new NoSuchElementException();
            }
            else if (nextItem == head) {
                head = nextItem.next;
            }
            else if(nextItem == tail) {
                tail = tail.prev;
            }
            else {
                nextItem.next.prev = nextItem.prev;
                nextItem.prev.next = nextItem.next;
            }
            size--;
            lastItemReturned = null;
        }

        @Override
        public void set(E e) {

        }

        public void add(E obj) {
            if (head == null) { // Add to an empty list.
                head = new Node<>(obj);
                tail = head;
            }
            else if (nextItem == head) { // Insert at head. // Create a new node.
                Node<E> newNode = new Node<>(obj);
// Link it to the nextItem.
                newNode.next = nextItem; // Step 1 // Link nextItem to the new node.
                nextItem.prev = newNode; // Step 2 // The new node is now the head.
                head = newNode;
            }
            else if (nextItem == null) { // Insert at tail. // Create a new node.
                Node<E> newNode = new Node<>(obj);
                // Link the tail to the new node.
                tail.next = newNode; // Step 1
                // Link the new node to the tail.
                newNode.prev = tail; // Step 2
                // The new node is the new tail.
                tail = newNode;
            } else {
                Node<E> newNode = new Node<>(obj);
                // Link it to nextItem.prev.
                newNode.prev = nextItem.prev; // Step 1
                nextItem.prev.next = newNode; // Step 2 // Link it to the nextItem.
                newNode.next = nextItem; // Step 3
                nextItem.prev = newNode; // Step 4
            }
            size++;
            index++;
        }
    }

    public KWListIter listIterator(int index) {
        return new KWListIter(index);
    }

    public void add(int index, E obj) {
        listIterator(index).add(obj);
    }

    public E get(int index) {
        return listIterator(index).next();
    }

    public void addFirst(E item) {
        add(0, item);
    }

    public void addLast(E item) {
        add(size, item);
    }

    public void remove(int index) {
        listIterator(index).remove();
    }

    public int getSize() {
        return size;
    }
}
