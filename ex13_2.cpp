#include "bits/stdc++.h"

struct Edge
{
    int P1, P2;
    int weight;
    Edge(int theP1, int theP2, int theWeight)
    {
        P1 = theP1;
        P2 = theP2;
        weight = theWeight;
    }
    Edge(const Edge &e)
    {
        P1 = e.P1;
        P2 = e.P2;
        weight = e.weight;
    }

    bool operator<(const Edge &x) const { return weight > x.weight; }
};

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

class graph
{
    int *pre;
    int gSize;
    int *rank; //并查集按秩合并

public:
    graph(int n) : gSize(n)
    {
        pre = new int[n + 1];
        rank = new int[n + 1];
        for (int i = 1; i <= gSize; ++i)
        {
            pre[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) const
    {
        if (pre[x] == x)
            return x;
        else
            return find(pre[x]);
    }

    bool unite(int x, int y)
    {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root)
            return false;
        if (rank[x_root] > rank[y_root])
            pre[y_root] = x_root;
        else if (rank[x_root] == rank[y_root])
        {
            pre[x_root] = y_root;
            rank[y_root]++;
        }
        else
            pre[x_root] = y_root;
        return true;
    }

    void Kruskal(int e)
    {
        long long int ans = 0;
        std::priority_queue<Edge> Q;
        while (e--)
        {
            int i = read(), j = read(), w = read();
            Edge E(i, j, w);
            Q.push(E);
        }

        int cnt = 0;
        while (!Q.empty())
        {
            Edge e(Q.top());
            Q.pop();
            if (unite(e.P1, e.P2))
                ans += e.weight;
            cnt++;
        }
        printf("%lld", ans);
    }
};

int main()
{
    int n = read(), e = read();
    graph G(n);
    G.Kruskal(e);
}