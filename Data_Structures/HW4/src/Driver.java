public class Driver {
    public static void main(String[] args) {
        System.out.println("==================Heap Structure Test=====================\n");
        System.out.println("Inserting some elements first...");
        Heap<Integer> heap = new Heap<>();
        for (int i = 0; i < 6; i++)
            heap.insertElement(i*2);
        heap.insertElement(4);
        heap.printHeap();
        System.out.println("==================Inserting element 9=====================\n");
        heap.insertElement(9);
        heap.printHeap();
        System.out.println("==================Removing 3rd largest element=====================\n");
        heap.printHeap();
        Heap<Integer> heap2 = new Heap<>();
        System.out.println("==================Creating new heap=====================\n");
        for (int i = 0; i < 6; i++)
            heap2.insertElement(i*3);
        heap2.printHeap();
        System.out.println("==================Merge with second heap=====================\n");
        heap.mergeHeap(heap2);
        heap.printHeap();
    }
}
