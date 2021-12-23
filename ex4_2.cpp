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
    void interSort();
    void remove(const T &theElement);
    int f();

    iterator<T> begin() const
    {
        iterator<T> it(firstNode);
        return it;
    }
    iterator<T> end() const
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
    for (; p->next->element != theElement and p->next != NULL; p = p->next)
        ;
    if (p->next == NULL)
        return;
    deleteNode = p->next;
    p->next = deleteNode->next;
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

template <class T>
void chain<T>::interSort()
{
    for (int i = 1; i < listsize; ++i)
    {
        T temp = get(i);
        int j;
        for (j = i - 1; j >= 0 and temp < get(j); --j)
            get(j + 1) = get(j);
        get(j + 1) = temp;
    }
}

template <class T>
void merge(const chain<T> &a, const chain<T> &b, chain<T> &c)
{
    int cnta = 0, cntb = 0;
    iterator<T> ita = a.begin();
    iterator<T> itb = b.begin();
    if (a.size() == 0)
    {
        for (; cntb < b.size(); ++cntb, ++itb)
            c.insert(cntb, *itb);
        return;
    }
    if (b.size() == 0)
    {
        for (; cnta < a.size(); ++cnta, ++ita)
            c.insert(cnta, *ita);
        return;
    }

    T tempa = *ita, tempb = *itb;
    while (cnta < a.size() or cntb < b.size())
    {
        if (tempa <= tempb)
        {
            c.insert(cnta + cntb, tempa);
            ++cnta;
            ++ita;
            if (cnta == a.size())
                break;
            tempa = *ita;
        }
        else
        {
            c.insert(cnta + cntb, tempb);
            ++cntb;
            ++itb;
            if (cntb == b.size())
                break;
            tempb = *itb;
        }
    }
    if (cnta == a.size())
    {
        for (; cntb < b.size(); ++cntb, ++itb)
            c.insert(cnta + cntb, *itb);
        return;
    }
    if (cntb == b.size())
    {
        for (; cnta < a.size(); ++cnta, ++ita)
            c.insert(cnta + cntb, *ita);
        return;
    }
}

int main()
{
    chain<int> a, b, c;
    int n, m;
    std::cin >> n >> m;
    for (size_t i = 0; i < n; ++i)
    {
        int temp = 0;
        std::cin >> temp;
        a.insert(0, temp);
    }
    for (size_t i = 0; i < m; ++i)
    {
        int temp;
        std::cin >> temp;
        b.insert(0, temp);
    }
    a.interSort();
    b.interSort();
    merge(a, b, c);
    c.output();
    // std::cout << a.f() << std::endl;
    // std::cout << b.f() << std::endl;
    // std::cout << c.f() << std::endl;
}