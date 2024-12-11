#include <iostream>
#include <string>

using namespace std;

template <typename T>
class maxHeap {
private:
    T* heap;
    int size;
    int capacity;
    const int initialCapacity;

    int parent(int i) {
        return (i - 1) / 2;
    }

    int leftChild(int i) {
        return 2 * i + 1;
    }

    int rightChild(int i) {
        return 2 * i + 2;
    }

    void resize(int newCapacity) {
        T* newHeap = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    void przekopcowaniewGore(int index) {
        T value = heap[index];
        int current = index;

        while (current > 0 && value > heap[parent(current)]) {
            heap[current] = heap[parent(current)];
            current = parent(current);
        }
        heap[current] = value;
    }

    void przekopcowaniewDol(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int largest = i;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            T temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;

            przekopcowaniewDolRec(largest);

        }

    }

public:

    maxHeap(int initialCapacity) : size(0), capacity(initialCapacity), initialCapacity(initialCapacity) {
        heap = new T[capacity];
    }

    ~maxHeap() {
        delete[] heap;
    }

    void addElement(T value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        heap[size] = value;
        przekopcowaniewGore(size);
        size++;
    }


    void removeMaxValue() {
        heap[0] = heap[size - 1];
        size--;

        przekopcowaniewDolRec(0);

    }


    void przekopcowaniewDolRec(int i) {
        przekopcowaniewDol(i);
    }

    void selfDestruction() {
        delete[] heap;
        heap = new T[initialCapacity];
        size = 0;
        capacity = initialCapacity;


    }


   string toString(int range) {
       if (range > size || range < size) {
           range = 10;
       }

       if (size == 0) {
           cout << endl << "heap is empty" << endl;
       }

       string res = "Size: ";
       res += to_string(size) + "\n";
       res += "Capacity: " + to_string(capacity);
       res += " \n { \n";
       for (int i = 0; i < range; i++) {
           res += to_string(heap[i]) + ", ";

       }
       res += "\n } ";

       return res;
    }

};

//a addElement+, b removeMaxValue+, c selfDesctruction+, d toString+, e+,f+

int main()
{
    
    maxHeap<int> heap(5);

    cout << "adding elements" << endl;
    heap.addElement(20);
    heap.addElement(25);
    heap.addElement(15);
    heap.addElement(30);

    cout << heap.toString(3);
        
    heap.removeMaxValue();
    cout << heap.toString(3);


    heap.selfDestruction();
    heap.toString(3);
}

