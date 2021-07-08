
public interface Collection<E> {
	public ColIterator<E> iterator();

	public boolean add(E e);

	public boolean addAll(Collection<E> c);

	public void clear();

	public boolean contains(E e);

	public boolean containsAll(Collection<E> c);

	public boolean isEmpty();

	public boolean remove(E e);

	public boolean removeAll(Collection<E> c);

	public boolean retainAll(Collection<E> c);

	public int size();
}