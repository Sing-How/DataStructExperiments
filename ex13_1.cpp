#include "bits/stdc++.h"

typedef long long ll;
using namespace std;

const int maxn = 5e6 + 10;

struct node
{
    int No;
    int weight;
    bool operator<(const node &x) const
    {
        return weight > x.weight;
    }
    node(int theNo, int theWeight)
    {
        No = theNo;
        weight = theWeight;
    }
};

int m, n;
bool vis[maxn];
vector<node> e[maxn];
priority_queue<node> q;

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

ll prim()
{
    ll ans = 0;
    int cnt = 0;
    node P(1, 0);
    q.push(P);
    while (!q.empty() and cnt <= n)
    {
        node k = q.top();
        q.pop();
        if (vis[k.No])
            continue;
        vis[k.No] = 1;
        ans += k.weight;
        cnt++;
        for (int i = 0; i < e[k.No].size(); ++i)
        {
            if (!vis[e[k.No][i].No])
            {
                P.No = e[k.No][i].No;
                P.weight = e[k.No][i].weight;
                q.push(P);
            }
        }
    }
    return ans;
}

int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i)
    {
        int x = read(), y = read(), z = read();
        node P1(y, z);
        node P2(x, z);
        e[x].push_back(P1);
        e[y].push_back(P2);
    }
    cout << prim() << endl;
    return 0;
}