#include <iostream>
#include <queue>
using namespace std;
template <class T>

struct cnode
{
    T element;
    cnode *next;
    cnode(T theelement)
    {
        element = theelement;
        next = NULL;
    }
    cnode(T theelement, cnode *thenext)
    {
        element = theelement;
        next = thenext;
    }
};
template <class T>

class glist
{
public:
    int LengthOfdfs, LengthOfbfs;
    glist(int m);
    void insert(int m, int n);
    int dele(int m, int n);
    void output();
    void output1();
    void output3(); //输出最小编号
    void bfs(int y, int z);
    void dfs(int y, int z);
    void flush();
    int CountOfLTFL();
    void MinNumOfLTZT();
    void Minpath(int x, int y);

private:
    cnode<T> *firstnode;
    cnode<T> *lastnode;
    cnode<T> **aList;
    int gsize;
    int *r, *a;
};
template <class T>

void glist<T>::flush()
{
    LengthOfdfs = 0;
    LengthOfbfs = 0;
    for (int i = 0; i <= gsize; i++)
    {
        r[i] = 0;
    }
}
template <class T>

glist<T>::glist(int m)
{
    //firstnode=lastnode=NULL;
    gsize = m;
    aList = new cnode<T> *[gsize + 1];
    r = new int[gsize + 1];
    a = new int[gsize + 1];
    for (int i = 0; i <= gsize; i++)
    {
        aList[i] = NULL;
        r[i] = 0;
        a[i] = 0;
    }
}

template <class T>
void glist<T>::insert(int m, int n)
{
    cnode<T> *p1 = aList[m];
    cnode<T> *pp = NULL, *p = NULL;
    cnode<T> *p2 = aList[n];
    if (p1 == NULL)
    {
        aList[m] = new cnode<T>(n);
    }
    else if (p1->element > n)
    {
        p = new cnode<T>(n, p1);
        aList[m] = p;
    }
    else
    {
        while (p1 != NULL && n > p1->element)
        {
            pp = p1;
            p1 = p1->next;
        } //找到n应该在的位置
        if (p1 == NULL)
        {
            pp->next = new cnode<T>(n, p1);
        }
        else
        {
            if (p1->element == n)
            {
                return;
            }
            pp->next = new cnode<T>(n, p1);
        }
    }
    pp = NULL;
    p = NULL;
    if (p2 == NULL)
    {
        aList[n] = new cnode<T>(m);
    }
    else if (p2->element > m)
    {
        p = new cnode<T>(m, p2);
        aList[n] = p;
    }
    else
    {
        while (p2 != NULL && m > p2->element)
        {
            pp = p2;
            p2 = p2->next;
        }
        if (p2 == NULL)
        {
            pp->next = new cnode<T>(m, p2);
        }
        else
        {
            if (p2->element == m)
            {
                return;
            }
            pp->next = new cnode<T>(m, p2);
        }
    }
    return;
}
template <class T>

int glist<T>::dele(int m, int n)
{
    cnode<T> *p1 = aList[m];
    cnode<T> *pp1 = NULL;
    cnode<T> *p2 = aList[n];
    cnode<T> *pp2 = NULL;
    while (p1 != NULL && p1->element != n)
    {
        pp1 = p1;
        p1 = p1->next;
    }
    if (pp1 == NULL)
    {
        if (p1 == NULL)
        {
            return -1;
        }
        else
        {
            aList[m] = p1->next;
            delete p1;
        }
    }
    else
    {
        if (p1 == NULL)
        {
            return -1;
        }
        else
        {
            pp1->next = p1->next;
            delete p1;
        }
    }
    while (p2 != NULL && p2->element != m)
    {
        pp2 = p2;
        p2 = p2->next;
    }
    if (pp2 == NULL)
    {
        if (p2 == NULL)
        {
            return -1;
        }
        else
        {
            aList[n] = p2->next;
            delete p2;
        }
    }
    else
    {
        if (p2 == NULL)
        {
            return -1;
        }
        else
        {
            pp2->next = p2->next;
            delete p2;
        }
    }
    return 1;
}
template <class T>

void glist<T>::output()
{
    int i;
    cnode<T> *p = NULL;
    for (i = 1; i <= gsize; i++)
    {
        p = aList[i];
        while (p != NULL)
        {
            cout << p->element << ends;
            p = p->next;
        }
        cout << endl;
    }
}
template <class T>

void glist<T>::output3()
{
    int i;
    for (i = 0; i <= gsize; i++)
    {
        if (a[i] != 0)
        {
            cout << a[i] << " ";
        }
    }
    cout << endl;
}
template <class T>

void glist<T>::bfs(int y, int z)
{ //广度优先搜索
    int i = 0, w;
    queue<int> q;
    r[y] = 1;
    q.push(y);
    while (!q.empty())
    {
        w = q.front();
        if (z != 0)
        {
            cout << w << " ";
        }
        LengthOfbfs++;
        q.pop();
        for (cnode<T> *u = aList[w]; u != NULL; u = u->next)
        {
            if (r[u->element] == 0)
            {
                q.push(u->element);
                r[u->element] = 1;
            }
        }
    }
}
template <class T>

void glist<T>::dfs(int y, int z)
{ //深度优先搜索
    if (z != 0)
    {
        cout << y << " ";
    }
    LengthOfdfs++;
    r[y] = 1;
    cnode<T> *p = aList[y];

    while (p != NULL)
    {
        if (r[p->element] == 0)
        {
            dfs(p->element, z);
        }
        p = p->next;
    }
}
template <class T>

void glist<T>::output1()
{
    int i;

    for (i = 1; i <= gsize; i++)
    {
        cout << r[i] << ends;
    }
}
template <class T>

void glist<T>::MinNumOfLTZT()
{ //求所有连通子图中最小点的编号
    int i, k = -1;
    for (i = 1; i <= gsize; i++)
    {
        if (r[i] == 0)
        {
            dfs(i, 0);
            a[++k] = i;
        }
    }
    return;
}
template <class T>

int glist<T>::CountOfLTFL()
{                   //求连通分量个数
    int i, sum = 0; //sum为连通分量个数
    for (i = 1; i <= gsize; i++)
    {
        if (r[i] == 0)
        {
            dfs(i, 0);
            sum++;
        }
    }
    return sum;
}
template <class T>

void glist<T>::Minpath(int x, int y)
{ //寻找最短路径
    int w, i;
    queue<int> q;
    q.push(x);
    r[q.front()] = 1;
    int path[gsize + 1];
    for (i = 0; i <= gsize; i++)
    {
        path[i] = 0;
    }
    while (!q.empty())
    {
        w = q.front();
        q.pop();
        cnode<T> *p = aList[w];
        while (p != NULL)
        {
            if (r[p->element] == 0)
            {
                if (p->element == y)
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
    cout << "-1" << endl;
}

int main()
{
    int i, n, m, s, t, o, t1, t2, q, *b;
    cin >> n >> m >> s >> t;
    glist<int> hh(n);
    for (i = 0; i < m; i++)
    {
        cin >> o;
        switch (o)
        {
        case 0:
            cin >> t1 >> t2;
            hh.insert(t1, t2);
            break;
        case 1:
            cin >> t1 >> t2;
            q = hh.dele(t1, t2);
            break;
        case 2:
            hh.output();
            break;
        default:
            break;
        }
    }
    hh.flush();
    q = hh.CountOfLTFL();
    cout << q << endl;
    hh.flush();
    hh.MinNumOfLTZT();
    hh.output3();
    hh.flush();
    hh.dfs(s, 0);
    cout << hh.LengthOfdfs << endl;
    hh.flush();
    hh.dfs(s, 1);
    cout << endl;
    hh.flush();
    hh.bfs(t, 0);
    cout << hh.LengthOfbfs << endl;
    hh.flush();
    hh.bfs(t, 1);
    cout << endl;
    hh.flush();
    hh.Minpath(s, t);
    return 0;
}
