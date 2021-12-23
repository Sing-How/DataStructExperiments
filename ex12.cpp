#include "bits/stdc++.h"
using namespace std;

struct cnode
{
    int element;
    cnode *next;
    cnode(int theElement)
    {
        element = theElement;
        next = NULL;
    }
    cnode(int theElement, cnode *theNext)
    {
        element = theElement;
        next = theNext;
    }
};

class glist
{
    // cnode *firstNode;
    // cnode *lastNode;
    cnode **aList;
    int gSize;
    int *r, *a;

public:
    int dfsLen, bfsLen;
    glist(int n);
    void flush();
    void insert(int, int);
    void remove(int, int);
    void outputMin();
    void bfs(int);
    void _bfs(int);
    void dfs(int);
    void _dfs(int);
    int countOfLTFT();
    void shortPath(int s, int t);
};

void glist::flush()
{
    dfsLen = 0;
    bfsLen = 0;
    for (int i = 1; i <= gSize; ++i)
        r[i] = 0;
}

glist::glist(int n)
{
    gSize = n;
    aList = new cnode *[n + 1];
    r = new int[n + 1];
    a = new int[n + 1];
    for (int i = 1; i <= gSize; ++i)
    {
        aList[i] = NULL;
        r[i] = 0;
        a[i] = 0;
    }
}

void glist::insert(int x, int y)
{
    cnode *p1 = aList[x];
    cnode *p2 = aList[y];
    cnode *pp = NULL, *p = NULL;

    if (p1 == NULL)
        aList[x] = new cnode(y);
    else if (p1->element > y)
    {
        p = new cnode(y, p1);
        aList[x] = p;
    }
    else
    {
        while (p1 != NULL and y > p1->element)
        {
            pp = p1;
            p1 = p1->next;
        }
        if (p1 == NULL)
            pp->next = new cnode(y, p1);
        else
        {
            if (p1->element == y)
                return;
            else
                pp->next = new cnode(y, p1);
        }
    }

    pp = NULL;
    p = NULL;
    if (p2 == NULL)
        aList[y] = new cnode(x);
    else if (p2->element > x)
    {
        p = new cnode(x, p2);
        aList[y] = p;
    }
    else
    {
        while (p2 != NULL and x > p2->element)
        {
            pp = p2;
            p2 = p2->next;
        }
        if (p2 == NULL)
            pp->next = new cnode(x, p2);
        else
        {
            if (p2->element == x)
                return;
            else
                pp->next = new cnode(x, p2);
        }
    }
    return;
}

void glist::remove(int x, int y)
{
    cnode *p1 = aList[x];
    cnode *p2 = aList[y];
    cnode *pp1 = NULL, *pp2 = NULL;
    while (p1 != NULL and p1->element != y)
    {
        pp1 = p1;
        p1 = p1->next;
    }
    if (pp1 == NULL)
    {
        if (p1 == NULL)
            return; //error：not exist such an edge
        else
        {
            aList[x] = p1->next;
            delete p1;
        }
    }
    else
    {
        if (p1 == NULL)
            return; //error：not exist such an edge
        else
        {
            pp1->next = p1->next;
            delete p1;
        }
    }

    while (p2 != NULL and p2->element != x)
    {
        pp2 = p2;
        p2 = p2->next;
    }
    if (pp2 == NULL)
    {
        if (p2 == NULL)
            return; //error：not exist such an edge
        else
        {
            aList[y] = p2->next;
            delete p2;
        }
    }
    else
    {
        if (p2 == NULL)
            return; //error：not exist such an edge
        else
        {
            pp2->next = p2->next;
            delete p2;
        }
    }
}

void glist::outputMin()
{
    int k = -1;
    for (int i = 1; i <= gSize; ++i)
    {
        if (r[i] == 0)
        {
            dfs(i);
            a[++k] = i;
            cout << i << ' ';
        }
    }
    cout << '\n';
}

void glist::dfs(int y)
{

    dfsLen++;
    r[y] = 1;
    cnode *p = aList[y];

    while (p != NULL)
    {
        if (r[p->element] == 0)
            dfs(p->element);
        p = p->next;
    }
}

void glist::_dfs(int y)
{
    cout << y << ' ';
    dfsLen++;
    r[y] = 1;
    cnode *p = aList[y];

    while (p != NULL)
    {
        if (r[p->element] == 0)
            _dfs(p->element);
        p = p->next;
    }
}

void glist::bfs(int y)
{
    queue<int> q;
    q.push(y);
    r[y] = 1;
    while (!q.empty())
    {
        int F = q.front();
        bfsLen++;
        q.pop();
        for (cnode *u = aList[F]; u != NULL; u = u->next)
        {
            if (r[u->element] == 0)
            {
                q.push(u->element);
                r[u->element] = 1;
            }
        }
    }
}

void glist::_bfs(int y)
{
    queue<int> q;
    q.push(y);
    r[y] = 1;
    while (!q.empty())
    {
        int F = q.front();
        cout << F << ' ';
        bfsLen++;
        q.pop();
        for (cnode *u = aList[F]; u != NULL; u = u->next)
        {
            if (r[u->element] == 0)
            {
                q.push(u->element);
                r[u->element] = 1;
            }
        }
    }
}

int glist::countOfLTFT()
{
    int ans = 0;
    for (int i = 1; i <= gSize; ++i)
    {
        if (r[i] == 0)
        {
            dfs(i);
            ans++;
        }
    }
    return ans;
}

void glist::shortPath(int s, int t)
{
    queue<int> q;
    q.push(s);
    r[q.front()] = 1;
    int path[gSize + 1];

    for (int i = 1; i <= gSize; ++i)
        path[i] = 0;

    while (!q.empty())
    {
        int w = q.front();
        q.pop();
        cnode *p = aList[w];
        while (p != NULL)
        {
            if (r[p->element] == 0)
            {
                if (p->element == t)
                {
                    cout << path[w] + 1 << endl;
                    return;
                }
                path[p->element] = path[w] + 1;
                q.push(p->element);
                r[p->element] = 1;
            }
            p = p->next;
        }
    }
    cout << -1 << endl;
}

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    glist G(n);
    while (m--)
    {
        bool opt;
        cin >> opt;
        if (!opt)
        {
            int t1, t2;
            cin >> t1 >> t2;
            G.insert(t1, t2);
        }
        else
        {
            int t1, t2;
            cin >> t1 >> t2;
            G.remove(t1, t2);
        }
    }

    G.flush();
    cout << G.countOfLTFT() << endl;

    G.flush();
    G.outputMin();

    G.flush();
    G.dfs(s);
    cout << G.dfsLen << endl;

    G.flush();
    G._dfs(s);
    cout << '\n';

    G.flush();
    G.bfs(t);
    cout << G.bfsLen << endl;

    G.flush();
    G._bfs(t);
    cout << '\n';

    G.flush();
    G.shortPath(s, t);
    return 0;
}