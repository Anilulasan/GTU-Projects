

//I made my iterator class an interface and implemented in my collections.
public interface ColIterator<E> {
	public abstract boolean hasNext();

	public abstract E next();

	public abstract void remove();

	public abstract int get_index();
}