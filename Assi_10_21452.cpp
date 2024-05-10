#include <iostream>
using namespace std;
#define MAX 50

class HeapSort
{
private:
    int *heap;
    int size;

    void heapify(int i, int n)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] > heap[largest])
            largest = left;

        if (right < n && heap[right] > heap[largest])
            largest = right;

        if (i != largest)
        {
            swap(heap[i], heap[largest]);
            heapify(largest, n);
        }

        return;
    }

public:
    HeapSort() : heap(new int[MAX]), size(0) {}

    void buildHeap()
    {
        for (int i = (size - 1) / 2; i >= 0; i--)
            heapify(i, size);
    }

    void heapSort()
    {
        for (int i = size - 1; i > 0; i--)
        {
            swap(heap[0], heap[i]);
            heapify(0, i);
        }
    }

    void printHeap()
    {
        cout << "Heap: ";
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }

    void insert(int data)
    {
        if (size >= MAX)
        {
            cout << "Heap is full! Cannot insert more elements.\n";
            return;
        }

        int index = size;
        heap[size++] = data;
        int parent = (index - 1) / 2;

        while (parent >= 0 && heap[parent] < heap[index])
        {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (parent - 1) / 2;
        }

        cout << "Element " << data << " inserted successfully.\n";
    }

    void remove()
    {
        if (size == 0)
        {
            cout << "Heap is empty! Cannot remove any element.\n";
            return;
        }

        int data = heap[0];
        swap(heap[0], heap[size - 1]);
        size--;
        heapify(0, size);

        cout << "Element " << data << " removed successfully.\n";
    }

    int top()
    {
        if (this->empty())
        {
            cout << "Heap is empty! No top element.\n";
            return -1;
        }

        return heap[0];
    }

    bool empty()
    {
        return size == 0;
    }

    void pop()
    {
        if (this->empty())
        {
            cout << "Heap is empty! Cannot pop any element.\n";
            return;
        }

        remove();
    }
};

int main()
{
    HeapSort heapSort;
    int choice;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Insert an element\n";
        cout << "2. Remove an element\n";
        cout << "3. Display the top element\n";
        cout << "4. Pop the top element\n";
        cout << "5. Sort the heap\n";
        cout << "6. Build Heap\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int data;
            cout << "Enter the element to insert: ";
            cin >> data;
            heapSort.insert(data);
            heapSort.printHeap();
            break;
        }
        case 2:
            heapSort.remove();
            heapSort.printHeap();
            break;
        case 3:
            cout << "Top element: " << heapSort.top() << endl;
            break;
        case 4:
            heapSort.pop();
            heapSort.printHeap();
            break;
        case 5:
            heapSort.heapSort();
            heapSort.printHeap();
            break;
        case 6:
            heapSort.buildHeap();
            heapSort.printHeap();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
