import java.lang.reflect.Array;
import java.util.Arrays;


public class HashSet<E> implements Set<E> {
	private E [] H_Set;
	private int filled = 0;
	private int capacity = 0;
	private final int INC_CAP = 5;

	@SuppressWarnings("unchecked")
	public HashSet() {
		this(5);
	}

	@SuppressWarnings("unchecked")
	public HashSet(int cap, E... virtualParam) {
		if (virtualParam.length > 0)
			throw new IllegalArgumentException("virtualParam can not have a value!!!");

		Class<?> type = virtualParam.getClass().getComponentType();
		H_Set = (E [])(Array.newInstance(type, cap));
		filled = 0;
		capacity = cap;
	}

	private class SetIterator implements ColIterator<E> {
		private int index = -1;

		@Override
		public boolean hasNext() {
			if (index+1 < filled)
				return true;
			return false;
		}

		@Override
		public E next() {
			return H_Set[++index];
		}

		@Override
		public void remove()throws UnsupportedOperationException {
			if (index < 0)
				throw new UnsupportedOperationException("Remove operation is not supported by this iterator");
		}

		public int get_index() {
			return index;
		}

	}

	public ColIterator<E> iterator() {
		return new SetIterator();
	}

	public void increase_capacity() {
		H_Set = Arrays.copyOf(H_Set, capacity+INC_CAP);
		capacity += INC_CAP;
	}

	public boolean add(E e) {
		if (contains(e))
			return false;
		if (filled == capacity)
			increase_capacity();
		H_Set[filled] = e;
		filled++;
		return true;
	}

	public boolean addAll(Collection<E> c) {
		if (c.isEmpty())
			return false;
		
		ColIterator<E> iter = c.iterator();
		while (iter.hasNext()) {
			this.add(iter.next());
		}
		return true;
	}

	public void clear() {
		filled = 0;
		capacity = 0;
		H_Set = null;
	}

	public boolean contains(E e) {
		ColIterator<E> iter = this.iterator();
		while(iter.hasNext()) {
			if (iter.next() == e)
				return true;
		}
		return false;
	}

	public boolean containsAll(Collection<E> c) {
		if (filled < 1 || filled < c.size())
			return false;
		ColIterator<E> iterp = c.iterator();
		while (iterp.hasNext()) {
			if (!this.contains(iterp.next()))
				return false;
		}
		return true;
	}

	public boolean isEmpty() {
		if (this.size() == 0)
			return true;
		return false;
	}

	@SuppressWarnings("unchecked")
	public boolean remove(E e) {
		if (filled == 0 || !this.contains(e))
			return false;


		boolean found = false;
		Class<?> type = H_Set.getClass().getComponentType();
		E [] temp = (E[])(Array.newInstance(type, capacity));
		ColIterator<E> iter = this.iterator();
		
		while (!found) {
			if (iter.next() == e) {
				found = true;
			}
			else {
				temp[iter.get_index()] = H_Set[iter.get_index()];
			}
		}
		filled--;

		H_Set = (E[])(Array.newInstance(type, capacity));
		int i;
		for (i = 0; i < filled; i++) {
			H_Set[i] = temp[i];
		}

		return true;
	}

	@SuppressWarnings("unchecked")
	public boolean removeAll(Collection<E> c) {
		if (filled == 0 || c.size() == 0)
			return false;

		ColIterator<E> iterp = c.iterator();
		while(iterp.hasNext()) {
			E item;
			item = iterp.next();
			if (this.contains(item))
				this.remove(item);
		}
		return true;
	}

	public boolean retainAll(Collection<E> c) {
		if (filled == 0 || c.size() == 0)
			return false;
		ColIterator<E> iter = this.iterator();
		while (iter.hasNext()) {
			E item = iter.next();
			if (c.contains(item))
				this.remove(item);
		}
		return true;
	}	

	public int size() {
		return filled;
	}
}











