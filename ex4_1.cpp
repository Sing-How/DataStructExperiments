#include "bits/stdc++.h"

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
struct chainNode
{
    T element;
    chainNode<T> *next;

    chainNode() {}
    chainNode(const T &element) { this->element = element; }
    chainNode(const T &element, chainNode<T> *next)
    {
        this->element = element;
        this->next = next;
    }
};

template <class T>
class iterator
{
    chainNode<T> *node;

public:
    iterator() { node = NULL; }
    iterator(chainNode<T> *thenode) { node = thenode; }
    ~iterator() { node = NULL; }

    T &operator*() const { return node->element; }
    T *operator->() const { return &node->element; }

    iterator &operator++()
    {
        node = node->next;
        return *this;
    }
    iterator operator++(int)
    {
        iterator old = *this;
        node = node->next;
        return old;
    }

    bool operator!=(const iterator right) const { return this->node != right.node; }
    bool operator==(const iterator right) const { return this->node == right.node; }
};

template <class T>
class chain : public linearList<T>
{
    bool checkIndex(int theIndex) const;
    int listsize;
    chainNode<T> *firstNode;

public:
    chain();
    chain(const chain<T> &);
    ~chain();

    bool empty() const { return listsize == 0; }
    int size() const { return listsize; }
    T &get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &theElement);
    void output() const;

    void reverse();
    void remove(const T &theElement);
    int f();

    void interSort();

    iterator<T> begin()
    {
        iterator<T> it(firstNode);
        return it;
    }
    iterator<T> end()
    {
        iterator<T> it(NULL);
        return it;
    }
};

template <class T>
bool chain<T>::checkIndex(int theIndex) const
{
    return true;
}

template <class T>
chain<T>::chain()
{
    firstNode = NULL;
    listsize = 0;
}

template <class T>
chain<T>::chain(const chain<T> &theList)
{
    listsize = theList.listsize;
    if (listsize == 0)
    {
        firstNode = NULL;
        return;
    }
    chainNode<T> *temp = theList.firstNode;
    firstNode = new chainNode<T>(temp->element);
    temp = temp->next;
    chainNode<T> *currentNode = firstNode;

    while (temp != NULL)
    {
        currentNode->next = new chainNode<T>(temp->element);
        currentNode = currentNode->next;
        temp = temp->next;
    }

    currentNode->next = NULL;
}

template <class T>
chain<T>::~chain()
{
    while (firstNode != NULL)
    {
        chainNode<T> *temp = firstNode->next;
        delete firstNode;
        firstNode = temp;
    }
}

template <class T>
T &chain<T>::get(int theIndex) const
{
    if (!checkIndex(theIndex))
        exit(-1);
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; ++i)
        currentNode = currentNode->next;
    return currentNode->element;
}

template <class T>
int chain<T>::indexOf(const T &theElement) const
{
    chainNode<T> *currentNode = firstNode;
    int index = 0;
    while (currentNode != NULL and currentNode->element != theElement)
    {
        currentNode = currentNode->next;
        index++;
    }

    if (currentNode == NULL)
        return -1;
    else
        return index;
}

template <class T>
void chain<T>::erase(int theIndex)
{
    if (!checkIndex(theIndex))
        return;
    chainNode<T> *deleteNode = NULL;
    if (theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; ++i)
            p = p->next;
        deleteNode = p->next;
        p->next = deleteNode->next;
    }
    delete deleteNode;
    listsize--;
}

template <class T>
void chain<T>::remove(const T &theElement)
{
    chainNode<T> *deleteNode = NULL;
    chainNode<T> *p = firstNode;
    if (p->element == theElement)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        for (; p->next != NULL and p->next->element != theElement; p = p->next)
            ;
        if (p->next == NULL)
        {
            std::cout << -1 << std::endl;
            return;
        }
        deleteNode = p->next;
        p->next = deleteNode->next;
    }
    delete deleteNode;
    listsize--;
}

template <class T>
void chain<T>::insert(int theIndex, const T &theElement)
{
    if (theIndex < 0 or theIndex > listsize)
        return;
    if (theIndex == 0)
        firstNode = new chainNode<T>(theElement, firstNode);
    else
    {
        chainNode<T> *pre = firstNode;
        for (int i = 0; i < theIndex - 1; ++i)
            pre = pre->next;
        pre->next = new chainNode<T>(theElement, pre->next);
    }
    ++listsize;
}

template <class T>
void chain<T>::output() const
{
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < listsize; ++i)
    {
        std::cout << currentNode->element << ' ';
        currentNode = currentNode->next;
    }
}

template <class T>
void chain<T>::reverse()
{
    chainNode<T> *suf1, *suf2;
    suf1 = firstNode->next;
    suf2 = suf1->next;
    firstNode->next = NULL;
    while (suf2 != NULL)
    {
        suf1->next = firstNode;
        firstNode = suf1;
        suf1 = suf2;
        suf2 = suf2->next;
    }
    suf1->next = firstNode;
    firstNode = suf1;
    suf1 = NULL;
}

template <class T>
int chain<T>::f()
{
    int ans = 0;
    int cnt = 0;
    for (iterator<T> it = this->begin(); it != this->end(); ++it)
    {
        ans += cnt ^ (*it);
        ++cnt;
    }
    return ans;
}

int main()
{
    chain<int> thechain;
    int n, q;
    std::cin >> n >> q;
    for (size_t i = 0; i < n; ++i)
    {
        int temp = 0;
        std::cin >> temp;
        thechain.insert(i, temp);
    }
    while (q--)
    {
        int ctrl = 0;
        std::cin >> ctrl;
        switch (ctrl)
        {
        case 1:
        {
            int idx = 0, val = 0;
            std::cin >> idx >> val;
            thechain.insert(idx, val);
            thechain.output();
            break;
        }
        case 2:
        {
            int val = 0;
            std::cin >> val;
            thechain.remove(val);
            thechain.output();
            break;
        }
        case 3:
            thechain.reverse();
            thechain.output();
            break;
        case 4:
        {
            int val = 0;
            std::cin >> val;
            std::cout << thechain.indexOf(val) << std::endl;
            break;
        }
        case 5:
            std::cout << thechain.f() << std::endl;
            break;
        default:
            break;
        }
    }
    return 0;
}