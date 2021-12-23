#include "bits/stdc++.h"
using namespace std;

template <class T>
class linearList
{
public:
    virtual ~linearList(){};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &get(int theIndex) const = 0;
    virtual int indexOf(const T &theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T &theElement) = 0;
};

template <class T>
class arrayList : public linearList<T>
{
    T *element;
    int arrayLength;
    int listSize;
    bool checkIndex(int theIndex) const;

public:
    arrayList();
    arrayList(int initialCapacity);
    arrayList(const arrayList<T> &);
    ~arrayList() { delete[] element; }

    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T &get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    T *firstP() const { return element; }
    void reverse();
    void merge(const arrayList<T> &a, const arrayList<T> &b);
    void output() const;
};

template <class T>
arrayList<T>::arrayList()
{
    arrayLength = 100000;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if (initialCapacity < 1)
        exit(-1);
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

template <class T>
bool arrayList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 or theIndex >= listSize)
        return false;
    else
        return true;
}

template <class T>
T &arrayList<T>::get(int theIndex) const
{
    if (checkIndex(theIndex))
        return element[theIndex];
    else
        cout << "theIndex is out of range" << endl;
    return element[0];
}

template <class T>
int arrayList<T>::indexOf(const T &theElement) const
{
    for (int i = 0; i < listSize; ++i)
    {
        if (element[i] == theElement)
            return i;
    }
    return -1;
}

template <class T>
void arrayList<T>::erase(int theIndex)
{
    if (!checkIndex(theIndex))
        return;
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T();
}

template <class T>
void arrayList<T>::insert(int theIndex, const T &theElement)
{
    if (theIndex < 0 or theIndex > listSize)
    {
        cout << "theIndex is out of range" << endl;
        return;
    }
    if (listSize == arrayLength)
    {
        T *temp = new T[arrayLength];
        copy(element, element + listSize, temp);
        delete[] element;
        element = new T[2 * arrayLength];
        copy(temp, temp + listSize, element);
        delete[] temp;
    }

    copy_backward(element + theIndex, element + listSize, element + listSize + 1); //此处不能用copy
    element[theIndex] = theElement;
    listSize++;
}

template <class T>
void arrayList<T>::reverse()
{
    T *temp;
    temp = new T[listSize];
    for (int i = 0; i < listSize; ++i)
        temp[i] = element[listSize - i - 1];
    copy(temp, temp + listSize, element);
    delete[] temp;
}

template <class T>
void arrayList<T>::output() const
{
    for (int i = 0; i < listSize; ++i)
        cout << element[i] << '\n';
}

template <class T>
void arrayList<T>::merge(const arrayList<T> &a, const arrayList<T> &b)
{
    T *temp;
    temp = new T[a.listSize + b.listSize];
    int ca = 0, cb = 0;
    while (ca != a.listSize or cb != b.listSize)
    {
        if (ca == a.listSize)
        {
            temp[ca + cb] = b.element[cb];
            ++cb;
            continue;
        }
        if (cb == b.listSize)
        {
            temp[ca + cb] = a.element[ca];
            ++ca;
            continue;
        }
        if (a.element[ca] < b.element[cb])
        {
            temp[ca + cb] = a.element[ca];
            ++ca;
        }
        else
        {
            temp[ca + cb] = b.element[cb];
            ++cb;
        }
    }
    this->element = new T[a.listSize + b.listSize];
    this->listSize = a.listSize + b.listSize;
    this->arrayLength = this->listSize;
    copy(temp, temp + a.listSize + b.listSize, this->element);
    delete[] temp;
}