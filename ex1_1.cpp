#include <bits/stdc++.h>
using namespace std;

int n;
bool ifexist[100000] = {0};
int a[100000];
int value = 0;
void Subset(int x)
{
    if (x == n)
    {
        int temp = 0;
        int cnt = 0;
        int p = 1;
        while (cnt < n)
        {
            if (ifexist[cnt])
            {
                temp += p * a[cnt];
                ++p;
            }
            ++cnt;
        }
        value ^= temp;
        return;
    }
    ifexist[x] = 0;
    Subset(x + 1);
    ifexist[x] = 1;
    Subset(x + 1);
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    Subset(0);
    cout << value << endl;
}