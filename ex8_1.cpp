#include "bits/stdc++.h"

class hashTable
{
    int **table;
    int dsize;
    int divisor;

public:
    hashTable(int theDivisor)
    {
        divisor = theDivisor;
        dsize = 0;

        table = new int *[divisor];
        for (size_t i = 0; i < divisor; ++i)
            table[i] = NULL;
    }
    ~hashTable()
    {
        for (int i = 0; i < divisor; ++i)
        {
            delete table[i];
            table[i] = NULL;
        }
        delete[] table;
    }
    int search(const int &theKey) const
    {
        int i = theKey % divisor;
        int j = i;
        do
        {
            if (table[j] == NULL or *table[j] == theKey)
                return j;
            j = (j + 1) % divisor;
        } while (j != i);

        return j;
    }

    void find(const int &theKey) const
    {
        int b = search(theKey);

        if (table[b] == NULL)
        {
            std::cout << -1 << std::endl;
            return;
        }
        else if (*table[b] != theKey)
        {
            std::cout << -1 << std::endl;
            return;
        }
        else
            std::cout << b << std::endl;
    }

    void insert(const int &theKey)
    {
        int b = search(theKey);

        if (table[b] == NULL)
        {
            table[b] = new int(theKey);
            dsize++;
            std::cout << b << std::endl;
            return;
        }
        else
        {
            if (*table[b] == theKey)
            {
                std::cout << "Existed" << std::endl;
                return;
            }
            else
            {
                //???????????
            }
        }
    }

    void remove(const int &theKey)
    {
        int cnt = 0;
        int b = search(theKey);
        if (table[b] == NULL)
        {
            std::cout << "Not Found" << std::endl;
            return;
        }
        delete table[b];
        table[b] = NULL;
        int nul = b;

        for (int i = (b + 1) % divisor; i != b and table[i] != NULL; i = (i + 1) % divisor)
        {
            if ((*table[i]) % divisor != i)
            {
                int to = (*table[i]) % divisor;
                if ((nul < i and nul >= to) or (nul >= to and to > i) or (to > i and i > nul))
                {
                    table[nul] = table[i];
                    table[i] = NULL;
                    nul = i;
                    cnt++;
                }
            }
        }
        std::cout << cnt << std::endl;
    }
};

int main()
{
    int D, m;
    std::cin >> D >> m;
    hashTable H(D);
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