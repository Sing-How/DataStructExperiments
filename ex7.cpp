#include "bits/stdc++.h"

template <class T>
class arrayQueue
{
    T *queue;
    int queueFront, queueSize, arrayLength;

public:
    arrayQueue()
    {
        queue = new T[10000];
        arrayLength = 10000;
        queueFront = 0;
        queueSize = 0;
    }
    arrayQueue(int initialCapicity)
    {
        if (initialCapicity < 0)
            exit(-1);
        arrayLength = initialCapicity;
        queue = new T[initialCapicity];
        queueFront = 0;
        queueSize = 0;
    }
    ~arrayQueue() { delete[] queue; }

    bool empty() { return queueSize == 0; }
    bool full() { return queueSize == arrayLength; }
    int size() { return queueSize; }

    void push(const T &theElement);
    void pop();
    void output() const;

    T &front() const { return queue[queueFront]; }
    T &back() const { return queue[(queueFront + queueSize) % arrayLength]; }
};

template <class T>
void arrayQueue<T>::push(const T &theElement)
{
    if (full())
    {
        T *temp = new T[2 * arrayLength];
        int cnt = 0;
        while (cnt < queueSize)
        {
            temp[cnt] = queue[(queueFront + cnt) % arrayLength];
            cnt++;
        }
        delete[] queue;
        queue = temp;
        queueFront = 0;
        arrayLength *= 2;
    }
    queue[(queueFront + queueSize) % arrayLength] = theElement;
    queueSize++;
}

template <class T>
void arrayQueue<T>::pop()
{
    if (empty())
        exit(-1);
    queue[queueFront].~T();
    queueFront += 1;
    queueFront %= arrayLength;
    queueSize -= 1;
}

template <class T>
void arrayQueue<T>::output() const
{
    for (size_t i = 0; i < queueSize; ++i)
        std::cout << queue[(queueFront + i) % arrayLength] << std::endl;
}

int main()
{
    arrayQueue<int> a;
    int n;
    std::cin >> n;
    for (size_t i = 1; i <= n; ++i)
        a.push(i);

    while (a.size() >= 2)
    {
        a.pop();
        int temp = a.front();
        a.pop();
        a.push(temp);
    }
    a.output();
}