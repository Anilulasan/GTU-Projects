import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class Heap <E extends Comparable<E>>{
    private ArrayList<E> data;

    @SuppressWarnings("unchecked")
    public Heap() {
        data = new ArrayList();
    }

    private class HeapIterator implements Iterator<E> {
        int index = 0;
        @Override
        public boolean hasNext() {
            if (index+1 < data.size())
                return true;
            return false;
        }

        @Override
        public E next() {
            return data.get(++index);
        }
        //Sets the value if value is smaller than its childs and heap doesn't have that value.
        public boolean setValue(E item) {
            if (item.compareTo(data.get(getLeftChildIndex(index))) == 1 && item.compareTo(data.get(getLeftChildIndex(index))) == 1
                && !checkOccurence(item)) {
                data.set(index, item);
                return true;
            }
            return false;
        }
    }

    //Searches an item and returns index.
    public int search(E item) {
        int i, index = -1;
        for (i = 0; i < data.size(); i++) {
            if (data.get(i) == item) {
                index = i;
                break;
            }
        }
        return index;
    }

    public boolean removeIthLargest(int what_largest) {
        int index;
        index = findLargest(what_largest);
        return removeElement(index);
    }

    public void mergeHeap(Heap<E> rightSide) {
        int i;
        for (i = 0; i < rightSide.data.size(); i++) {
            insertElement(rightSide.data.get(i));
        }
    }

    public boolean insertElement(E item) {
        if (checkOccurence(item))
            return false;

        int index, parent_index;
        data.add(item);
        index = data.size()-1;
        parent_index = getParentIndex(index);
        while (index != 0 && (data.get(index).compareTo(data.get(parent_index)) == -1)) {
            swap(index, parent_index);
            index = parent_index;
            parent_index = getParentIndex(index);
        }
        return true;
    }

    //Removes the root node by replacing it with LIH.

    public boolean removeElement(E item) {
        if (data.size() == 0)
            return false;
        int index = search(item), child_index;
        swap(index, data.size()-1);
        data.remove(data.size()-1);
        child_index = findSmallestChild(index);
        while (child_index != -1) {
            swap(index, child_index);
            index = child_index;
            child_index = findSmallestChild(index);
        }
        return true;
    }

    public boolean removeElement(int itemIndex) {
        if (itemIndex < 0 || itemIndex > data.size())
            return false;
        int index = itemIndex, child_index;
        swap(index, data.size()-1);
        data.remove(data.size()-1);
        child_index = findSmallestChild(index);
        while (child_index != -1) {
            swap(index, child_index);
            index = child_index;
            child_index = findSmallestChild(index);
        }
        return true;
    }

    //Checks If heap structure has the item.
    public boolean checkOccurence(E item) {
        int i;
        boolean found = false;
        for (i = 0; i < data.size(); i++) {
            if (data.get(i).equals(item)) {
                found = true;
                break;
            }
        }
        return found;
    }

    public int getParentIndex(int childIndex) {
        int res;
        if (childIndex%2 == 0)
            res = (childIndex-2)/2;
        else
            res = (childIndex-1)/2;
        return res;
    }

    public int getLeftChildIndex(int index) {
        int res = 2*index+1;
        if (res > data.size())
            return -1;
        return res;
    }

    public int getRightChildIndex(int index) {
        int res = 2*index+2;
        if (res > data.size())
            return -1;
        return res;
    }

    public boolean swap(int index1, int index2) throws IndexOutOfBoundsException{
        E temp;
        temp = data.get(index1);
        data.set(index1, data.get(index2));
        data.set(index1, temp);
        return true;
    }

    //Finds smallest child index and returns. If there is no child, returns -1.
    public int findSmallestChild(int index) {
       int l_child_index, r_child_index, l_child_data, r_child_data;
       l_child_index = getLeftChildIndex(index);
       r_child_index = getRightChildIndex(index);
       if (r_child_index == -1 && l_child_index != -1)
           return l_child_index;
       else if (l_child_index == -1 && r_child_index != -1)
           return r_child_index;
       else if(l_child_index != -1 && r_child_index != -1) {
           if (data.get(l_child_index).compareTo(data.get(r_child_index)) == -1)
               return l_child_index;
           else
               return r_child_index;
       }
       return -1;
    }

    //Finds the ith largest element and returns its index.
    public int findLargest(int num) {
       E last_max, max;
       last_max = data.get(0);
       max = last_max;
       for (int i = 0; i < num; i++) {
           for (int j = 0; j < data.size(); j++) {
               if (i == 0) {
                   if (data.get(j).compareTo(max) == 1)
                       max = data.get(j);
               }
               else if (data.get(j).compareTo(last_max) == -1 && data.get(j).compareTo(max) == 1) {
                   max = data.get(j);
               }
           }
           last_max = max;
           max = data.get(0);
       }
        return search(max);
    }

    public int printHeap() {
        int i, j, height = findHeight(data.size()), cursor = 1;
        printSpace(power(2, height-1)-1);
        System.out.println(data.get(0));
        for (i = 1; i < height; i++) {
            printSpace(power(2, height-i-1)-1);
            for (j = 0; j < i*2; j++) {

                System.out.print(data.get(cursor+j));
                printSpace(power(2, height-i)-1);
                if (cursor+j == data.size()-1) {
                    System.out.println();
                    return 0;
                }
            }
            cursor += i*2;
            System.out.println();
        }
        System.out.println();
        return 1;
    }

    public int findHeight(int size) {
        int i = 0, height = 0;
        while (size > Math.pow(2, i)-1) {
            height++;
            i++;
        }
        return height;
    }

    public void printSpace(int count) {
        int i;
        for (i = 0; i < count; i++) {
            System.out.print(" ");
        }
    }

    public int power(int base, int exp) {
        if (exp == 0)
            return 1;
        int i, num = base;
        for (i = 1; i < exp; i++) {
            num *= base;
        }
        return num;
    }
}
