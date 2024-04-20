#include <iostream>
using namespace std;

class HeapSort
{
private:
    int *heapArray;
    int heapSize;

    void heapify(int arr[], int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    HeapSort(int arr[], int size)
    {
        heapArray = arr;
        heapSize = size;
    }

    void buildHeap()
    {
        for (int i = heapSize / 2 - 1; i >= 0; i--)
            heapify(heapArray, heapSize, i);
    }

    void heapSort()
    {
        buildHeap();
        for (int i = heapSize - 1; i > 0; i--)
        {
            swap(heapArray[0], heapArray[i]);
            heapify(heapArray, i, 0);
        }
    }

    void printArray()
    {
        cout << "Sorted Array: ";
        for (int i = 0; i < heapSize; i++)
            cout << heapArray[i] << " ";
        cout << endl;
    }
};

int main()
{
    int choice;
    do
    {
        cout << "Menu:\n";
        cout << "1. Sort an array\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int size;
            cout << "Enter the size of the array: ";
            cin >> size;

            int *arr = new int[size];
            cout << "Enter " << size << " integers: ";
            for (int i = 0; i < size; i++)
                cin >> arr[i];

            HeapSort heapSort(arr, size);
            heapSort.heapSort();
            heapSort.printArray();

            delete[] arr;
            break;
        }
        case 2:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 2);

    return 0;
}
