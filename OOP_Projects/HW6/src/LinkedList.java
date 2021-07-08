import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.NoSuchElementException;

public class LinkedList<E> implements List<E>, Queue<E> {
	private E [] L_List;
	private int filled = 0;
	private int capacity = 0;
	private final int INC_CAP = 5;

	@SuppressWarnings("unchecked")
	public LinkedList() {
		this(5);
	}

	@SuppressWarnings("unchecked")
	public LinkedList(int cap, E... virtualParam) {
		if (virtualParam.length > 0)
			throw new IllegalArgumentException("virtualParam can not have a value!!!");

		Class<?> type = virtualParam.getClass().getComponentType();
		L_List = (E [])(Array.newInstance(type, cap));
		filled = 0;
		capacity = cap;
	}

	private class LListIterator implements ColIterator<E> {
		private int index = -1;

		@Override
		public boolean hasNext() {
			if (index+1 < filled)
				return true;
			return false;
		}

		@Override
		public E next() {
			return L_List[++index];
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
		return new LListIterator();
	}

	public void increase_capacity() {
		capacity += INC_CAP;
		L_List = Arrays.copyOf(L_List, capacity);
		
	}

	public boolean add(E e) {
		if (filled == capacity)
			increase_capacity();
		L_List[filled] = e;
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
		L_List = null;
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
		Class<?> type = L_List.getClass().getComponentType();
		E [] temp = (E[])(Array.newInstance(type, capacity));
		ColIterator<E> iter = this.iterator();
		
		while (!found) {
			if (iter.next() == e) {
				found = true;
			}
			else {
				temp[iter.get_index()] = L_List[iter.get_index()];
			}
		}
		filled--;

		L_List = (E[])(Array.newInstance(type, capacity));
		int i;
		for (i = 0; i < filled; i++) {
			L_List[i] = temp[i];
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

	@Override
	public E element()throws NoSuchElementException {
		if (this.isEmpty())
			throw new NoSuchElementException("There is no elements in list.");
		return L_List[0];
	}

	public boolean offer(E e) {
		this.add(e);
		return true;
	}

	@SuppressWarnings("unchecked")
	public E poll() {
		if (this.isEmpty())
			return null;
		if (filled == 1)
			return L_List[0];
		int i;
		E head = L_List[0];

		Class<?> type = L_List.getClass().getComponentType();
		E [] temp = (E[])(Array.newInstance(type, capacity));

		for (i = 1; i < filled; i++) {
			temp[i] = L_List[i]; 
		}

		filled--;
		L_List = (E[])(Array.newInstance(type, capacity));
		for (i = 0; i < filled; i++) {
			L_List[i] = temp[i];
		}

		return head;
	}
}



