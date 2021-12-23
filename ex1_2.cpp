#include <bits/stdc++.h>
using namespace std;

int a[100000];
int b[100000];
bool ifexist[100000] = {0};
int n;
int value;

void output()
{
    int temp = 0;
    for (int i = 0; i < n; ++i)
        temp += (i + 1) ^ a[i];
    value |= temp;
}

void dfs(int x) //深度优先搜索，第x位的情况 
{
    if (x == n)
    {
        output();
        return;
    }
    for (int i = 0; i < n; ++i)
    {
        if (ifexist[i] == 0)
        {
            ifexist[i] = 1;
            a[x] = b[i];
            dfs(x + 1);
            ifexist[i] = 0;
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> b[i];
    dfs(0);
    cout << value << endl;
}