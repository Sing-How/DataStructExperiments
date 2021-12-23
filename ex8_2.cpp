#include "bits/stdc++.h"

struct hashNode
{
    int key;
    hashNode *next;
    hashNode(int theKey, hashNode *theNext) : key(theKey), next(theNext) {}
};

class hashtable
{
    hashNode **table;
    int *dsize;
    int divisor;

public:
    hashtable(int theDivisor)
    {
        divisor = theDivisor;
        dsize = new int[divisor];
        table = new hashNode *[divisor];
        for (size_t i = 0; i < divisor; ++i)
        {
            dsize[i] = 0;
            table[i] = NULL;
        }
    }
    ~hashtable()
    {
        for (size_t i = 0; i < divisor; ++i)
            delete[] table[i];
        delete[] table;
    }

    void find(const int &theKey) const
    {
        int theBucket = theKey % divisor;
        hashNode *currentNode = table[theBucket];
        int cnt = 0;
        while (currentNode != NULL and currentNode->key != theKey)
        {
            currentNode = currentNode->next;
        }
        if (currentNode == NULL)
        {
            std::cout << "Not Found" << std::endl;
            return;
        }
        else
        {
            std::cout << dsize[theBucket] << std::endl;
            return;
        }
    }

    void insert(const int &theKey)
    {
        int theBucket = theKey % divisor;
        hashNode *currentNode = table[theBucket];
        while (currentNode != NULL)
        {
            if (currentNode->key == theKey)
            {
                std::cout << "Existed" << std::endl;
                return;
            }
            currentNode = currentNode->next;
        }
        table[theBucket] = new hashNode(theKey, table[theBucket]);
        ++dsize[theBucket];
    }

    void remove(const int &theKey)
    {
        int theBucket = theKey % divisor;
        hashNode *preNode = table[theBucket];
        if (preNode == NULL)
        {
            std::cout << "Delete Failed" << std::endl;
            return;
        }
        if (preNode->key == theKey)
        {
            table[theBucket] = preNode->next;
            delete preNode;
            --dsize[theBucket];
            std::cout << dsize[theBucket] << std::endl;
            return;
        }
        hashNode *currentNode = table[theBucket]->next;
        while (currentNode != NULL)
        {
            if (currentNode->key == theKey)
            {
                preNode->next = currentNode->next;
                delete currentNode;
                --dsize[theBucket];
                std::cout << dsize[theBucket] << std::endl;
                return;
            }
            preNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode == NULL)
        {
            std::cout << "Delete Failed" << std::endl;
            return;
        }
    }
};

int main()
{
    int D, m;
    std::cin >> D >> m;
    hashtable H(D);
    while (m--)
    {
        int opt, x;
        std::cin >> opt >> x;
        switch (opt)
        {
        case 0:
            H.insert(x);
            break;
        case 1:
            H.find(x);
            break;
        case 2:
            H.remove(x);
            break;
        default:
            break;
        }
    }
    return 0;
}