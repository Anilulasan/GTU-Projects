import java.util.ArrayList;

public class Driver{
	public static void main(String[] args) {
		System.out.println("\n-----------------Hash Set integer--------------------\n");
		test_HSet_int();
		System.out.println("\n-----------------Array List integer--------------------\n");
		test_AList_int();
		System.out.println("\n-----------------Linked List integer--------------------\n");
		test_LList_int();
		System.out.println("\n-----------------Hash Set string--------------------\n");
		test_HSet_str();
		System.out.println("\n-----------------Array List string--------------------\n");
		test_AList_str();
		System.out.println("\n-----------------Linked List string--------------------\n");
		test_LList_str();
	}

	public static void test_HSet_int() {
		int i;
		ArrayList<Integer> H_set = new ArrayList<Integer>();
		System.out.println("\n-----------------size() test--------------------\n :%d"+H_set.size());
		
		System.out.println("\n-----------------add() test--------------------\n");
		for (i = 0; i < 10; i++) {
			H_set.add(i);
		}

		System.out.println("Size = \n"+H_set.size());
		
		System.out.println("\n-----------------clear() test--------------------\n");
		System.out.println("Size = \n"+H_set.size());

		System.out.println("\n-----------------contains() test--------------------\n");
		System.out.println("Contains = \n"+H_set.contains(0));

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+H_set.isEmpty());
		System.out.println("\nSome elements added\n");
		H_set.add(5);

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+H_set.isEmpty());

		System.out.println("\n-----------------remove() test--------------------\n");
		H_set.remove(5);
		System.out.println("Result = \n"+H_set.isEmpty());

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Contains = \n"+H_set.isEmpty());
	}

	public static void test_LList_int() {
		int i;
		ArrayList<Integer> linkedList = new ArrayList<Integer>();
		System.out.println("\n-----------------size() test--------------------\n :"+linkedList.size());
		
		System.out.println("\n-----------------add() test--------------------\n");
		for (i = 0; i < 10; i++) {
			linkedList.add(i);
		}

		System.out.println("Size = \n"+linkedList.size());
		
		System.out.println("\n-----------------clear() test--------------------\n");
		System.out.println("Size = \n"+linkedList.size());

		System.out.println("\n-----------------contains() test--------------------\n");
		System.out.println("Contains = \n"+linkedList.contains(0));

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+linkedList.isEmpty());
		System.out.println("\nSome elements added\n");
		linkedList.add(5);

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+linkedList.isEmpty());

		System.out.println("\n-----------------remove() test--------------------\n");
		linkedList.remove(5);
		System.out.println("Result = \n"+linkedList.isEmpty());

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Contains = \n"+linkedList.isEmpty());
	}

	public static void test_AList_int() {
		int i;
		ArrayList<Integer> arrlist = new ArrayList<Integer>();
		System.out.println("\n-----------------size() test--------------------\n :"+arrlist.size());
		
		System.out.println("\n-----------------add() test--------------------\n");
		for (i = 0; i < 10; i++) {
			arrlist.add(i);
		}

		System.out.println("Size = \n"+arrlist.size());
		
		System.out.println("\n-----------------clear() test--------------------\n");
		System.out.println("Size = \n"+arrlist.size());

		System.out.println("\n-----------------contains() test--------------------\n");
		System.out.println("Contains = \n"+arrlist.contains(0));

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+arrlist.isEmpty());
		System.out.println("\nSome elements added\n");
		arrlist.add(5);

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+arrlist.isEmpty());

		System.out.println("\n-----------------remove() test--------------------\n");
		arrlist.remove(5);
		System.out.println("Result = \n"+arrlist.isEmpty());

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Contains = \n"+arrlist.isEmpty());
	}

	public static void test_HSet_str() {
		int i;
		ArrayList<String> H_set = new ArrayList<String>();
		System.out.println("\n-----------------size() test--------------------\n :"+H_set.size());
		
		System.out.println("\n-----------------add() test--------------------\n");
		H_set.add("asd");

		System.out.println("Size = \n"+H_set.size());
		
		System.out.println("\n-----------------clear() test--------------------\n");
		System.out.println("Size = \n"+H_set.size());

		System.out.println("\n-----------------contains() test--------------------\n");
		System.out.println("Contains = \n"+H_set.contains("asd"));

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+H_set.isEmpty());
		System.out.println("\nSome elements added\n");
		H_set.add("werwer");

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+H_set.isEmpty());

		System.out.println("\n-----------------remove() test--------------------\n");
		H_set.remove("werwer");
		System.out.println("Result = \n"+H_set.isEmpty());

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+H_set.isEmpty());
	}

	public static void test_LList_str() {
		int i;
		ArrayList<String> linkedList = new ArrayList<String>();
		System.out.println("\n-----------------size() test--------------------\n :"+linkedList.size());
		
		System.out.println("\n-----------------add() test--------------------\n");
		linkedList.add("asd");

		System.out.println("Size = \n"+linkedList.size());
		
		System.out.println("\n-----------------clear() test--------------------\n");
		System.out.println("Size = \n"+linkedList.size());

		System.out.println("\n-----------------contains() test--------------------\n");
		System.out.println("Contains = \n"+linkedList.contains("asd"));

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+linkedList.isEmpty());
		System.out.println("\nSome elements added\n");
		linkedList.add("asd");

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+linkedList.isEmpty());

		System.out.println("\n-----------------remove() test--------------------\n");
		linkedList.remove(5);
		System.out.println("Result = \n"+linkedList.isEmpty());

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+linkedList.isEmpty());
	}

	public static void test_AList_str() {
		int i;
		ArrayList<String> arrlist = new ArrayList<String>();
		System.out.println("\n-----------------size() test--------------------\n :"+arrlist.size());
		
		System.out.println("\n-----------------add() test--------------------\n");
		arrlist.add("asd");

		System.out.println("Size = \n"+arrlist.size());
		
		System.out.println("\n-----------------clear() test--------------------\n");
		System.out.println("Size = \n"+arrlist.size());

		System.out.println("\n-----------------contains() test--------------------\n");
		System.out.println("Contains = \n"+arrlist.contains("asd"));

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+arrlist.isEmpty());
		System.out.println("\nSome elements added\n");
		arrlist.add("ertert");

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+arrlist.isEmpty());

		System.out.println("\n-----------------remove() test--------------------\n");
		arrlist.remove("ertert");
		System.out.println("Result = \n"+arrlist.isEmpty());

		System.out.println("\n-----------------isEmpty() test--------------------\n");
		System.out.println("Result = \n"+arrlist.isEmpty());
	}
}