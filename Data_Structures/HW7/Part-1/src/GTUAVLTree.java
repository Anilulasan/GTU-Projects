import java.util.*;

public class GTUAVLTree<E extends Comparable<E>> implements NavigableSet {
    private AVLTree<E> avlTree;

    public GTUAVLTree() {
        avlTree = new AVLTree<>();
    }

    @Override
    public boolean add(Object o) {
        return avlTree.add((E)o);
    }

    @Override
    public Object last() {
        return null;
    }

    @Override
    public Object lower(Object o) {
        return null;
    }

    @Override
    public Object floor(Object o) {
        return null;
    }

    @Override
    public Object ceiling(Object o) {
        return null;
    }

    @Override
    public Object higher(Object o) {
        return null;
    }

    @Override
    public Object pollFirst() {
        return null;
    }

    @Override
    public Object pollLast() {
        return null;
    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean contains(Object o) {
        return false;
    }

    @Override
    public Iterator iterator() {
        return null;
    }

    @Override
    public Object[] toArray() {
        return new Object[0];
    }

    @Override
    public boolean remove(Object o) {
        return false;
    }

    @Override
    public boolean addAll(Collection c) {
        return false;
    }

    @Override
    public void clear() {

    }

    @Override
    public boolean removeAll(Collection c) {
        return false;
    }

    @Override
    public boolean retainAll(Collection c) {
        return false;
    }

    @Override
    public boolean containsAll(Collection c) {
        return false;
    }

    @Override
    public Object[] toArray(Object[] a) {
        return new Object[0];
    }

    @Override
    public NavigableSet descendingSet() {
        return null;
    }

    @Override
    public Iterator descendingIterator() {
        return null;
    }

    @Override
    public NavigableSet subSet(Object fromElement, boolean fromInclusive, Object toElement, boolean toInclusive) {
        return null;
    }

    @Override
    public NavigableSet headSet(Object toElement, boolean inclusive) {
        return null;
    }

    @Override
    public NavigableSet tailSet(Object fromElement, boolean inclusive) {
        return null;
    }

    @Override
    public Comparator comparator() {
        return null;
    }

    @Override
    public SortedSet subSet(Object fromElement, Object toElement) {
        return null;
    }

    @Override
    public SortedSet headSet(Object toElement) {
        return null;
    }

    @Override
    public SortedSet tailSet(Object fromElement) {
        return null;
    }

    @Override
    public Object first() {
        return null;
    }
}
