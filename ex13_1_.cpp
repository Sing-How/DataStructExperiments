#include "bits/stdc++.h"
using namespace std;

typedef struct cnode
{
    int element;
    int weight;
    cnode *next;
    cnode(int theElement, int theWeight)
    {
        element = theElement;
        weight = theWeight;
        next = NULL;
    }
    cnode(int theElement, int theWeight, cnode *theNext)
    {
        element = theElement;
        weight = theWeight;
        next = theNext;
    }
    bool operator<(const cnode &x) const
    {
        return weight > x.weight;
    }
} cnode;

class graphList
{
    cnode **aList;
    int gSize;

public:
    graphList(int n)
    {
        gSize = n;
        aList = new cnode *[n + 1];
        for (int i = 0; i <= gSize; ++i)
            aList[i] = NULL;
    }

    void insert(int, int, int);
    long long int Prim();
};

void graphList::insert(int x, int y, int w)
{
    cnode *p1 = aList[x];
    cnode *p2 = aList[y];

    aList[x] = new cnode(y, w, p1);

    aList[y] = new cnode(x, w, p2);

    return;
}

long long int graphList::Prim()
{
    bool vis[gSize + 1];
    for (int i = 1; i <= gSize; ++i)
        vis[i] = 0;
    priority_queue<cnode> q;
    long long int ans = 0;
    int cnt = 0;
    cnode P(1, 0);
    q.push(P);
    while (!q.empty() and cnt <= gSize)
    {
        cnode k = q.top();
        q.pop();
        if (vis[k.element])
            continue;
        vis[k.element] = 1;
        ans += k.weight;
        cnt++;
        cnode *p = aList[k.element];
        while (p != NULL)
        {
            if (!vis[p->element])
            {
                P.element = p->element;
                P.weight = p->weight;
                q.push(P);
            }
            p = p->next;
        }
    }
    return ans;
}

inline int read()
{
    char ch = getchar();
    int s = 0, f = 1;
    while (!(ch >= '0' && ch <= '9'))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = (s << 3) + (s << 1) + ch - '0';
        ch = getchar();
    }
    return s * f;
}

int main()
{
    int n, e;
    n = read();
    e = read();
    graphList G(n);
    while (e--)
    {
        int i = read(), j = read(), w = read();

        G.insert(i, j, w);
    }
    cout << G.Prim() << endl;
}