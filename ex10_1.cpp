#include "bits/stdc++.h"

template <class T>
class minHeap
{
    T *heap;
    int heapSize, arrayLength;

public:
    minHeap()
    {
        heapSize = 0;
        arrayLength = 10000;
        heap = new T[arrayLength];
    }

    minHeap(T *theHeap, int theSize)
    {
        arrayLength = 10000;
        heap = new T[arrayLength];
        std::copy(theHeap, theHeap + theSize + 1, heap);
        heapSize = theSize;
        for (int root = heapSize / 2; root >= 1; --root)
        {
            T rootElement = heap[root];

            int child = 2 * root;
            while (child <= heapSize)
            {
                if (child < heapSize and heap[child] > heap[child + 1])
                    child++;

                if (rootElement <= heap[child])
                    break;

                heap[child / 2] = heap[child];
                child *= 2;
            }
            heap[child / 2] = rootElement;
        }
    }

    ~minHeap() { delete[] heap; }

    bool empty()
    {
        return heapSize == 0;
    }

    void push(const T theElement)
    {
        if (heapSize == arrayLength - 1)
        {
            T *temp = new T[2 * arrayLength];
            arrayLength *= 2;
            std::copy(heap, heap + arrayLength, temp);
            delete[] heap;
            heap = temp;
        }
        int currentNode = ++heapSize;
        while (currentNode != 1 and heap[currentNode / 2] > theElement)
        {
            heap[currentNode] = heap[currentNode / 2];
            currentNode /= 2;
        }
        heap[currentNode] = theElement;
    }

    void pop()
    {
        heap[1].~T();

        T lastElement = heap[heapSize--];
        int currentNode = 1, child = 2;
        while (child <= heapSize)
        {
            if (child < heapSize and heap[child] > heap[child + 1])
                ++child;

            if (lastElement <= heap[child])
                break;

            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }
        heap[currentNode] = lastElement;
    }

    T top() const
    {
        return heap[1];
    }
};

int main()
{
    int n, m;
    std::cin >> n;
    int *theHeap = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        std::cin >> theHeap[i];
    minHeap<int> H(theHeap, n);
    std::cout << H.top() << std::endl;
    std::cin >> m;
    while (m--)
    {
        int opt;
        std::cin >> opt;
        switch (opt)
        {
        case 1:
            int num;
            std::cin >> num;
            H.push(num);
            std::cout << H.top() << std::endl;
            break;
        case 2:
            H.pop();
            std::cout << H.top() << std::endl;
            break;
        case 3:
        {
            std::cin >> n;
            int *theHeap1 = new int[n + 1];
            for (int i = 1; i <= n; ++i)
                std::cin >> theHeap1[i];
            minHeap<int> H1(theHeap1, n);
            while (!H1.empty())
            {
                std::cout << H1.top() << ' ';
                H1.pop();
            }
            std::cout << std::endl;
            break;
        }
        default:
            break;
        }
    }
}