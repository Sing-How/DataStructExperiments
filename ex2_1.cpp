#include <bits/stdc++.h>
using namespace std;

template <class T>
class Sort
{
    T *a;
    int n;

public:
    Sort() {}
    Sort(int n)
    {
        this->n = n;
        a = new T[n];
        for (int i = 0; i < n; ++i)
            cin >> a[i];
    }

    void output()
    {
        for (int i = 0; i < n; ++i)
            cout << a[i] << ' ';
    }
    void rank_sort() //名次排序
    {
        int *r;
        r = new int[n];
        for (int i = 0; i < n; ++i)
            r[i] = 0;

        for (int i = 1; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (a[j] <= a[i])
                    r[i]++;
                else
                    r[j]++;

        int *temp;
        temp = new T[n];
        for (int i = 0; i < n; ++i)
            temp[r[i]] = a[i];
        for (int i = 0; i < n; ++i)
            a[i] = temp[i];
        delete[] temp;
    }
    void select_sort() //选择排序
    {
        bool sorted = false;
        int p = n;
        while (!sorted)
        {
            int maxpos = 0;
            sorted = true;
            for (int i = 1; i < p; ++i)
            {
                if (a[i] >= a[maxpos])
                    maxpos = i;
                else
                    sorted = false;
            }
            swap(a[maxpos], a[--p]);
        }
    }
    void bubble_sort() //冒泡排序
    {
        for (int i = 1; i < n; ++i)
        {
            bool swapped = false;
            for (int j = n - 1; j >= i; --j)
                if (a[j] < a[j - 1])
                {
                    swap(a[j], a[j - 1]);
                    swapped = true;
                }
            if (!swapped)
                return;
        }
    }
    void insert_sort() //插入排序
    {
        for (int i = 0; i < n; ++i)
        {
            T temp = a[i];
            int j = 0;
            for (j = i - 1; j >= 0 and temp < a[j]; --j)
                a[j + 1] = a[j];
            a[j + 1] = temp;
        }
    }
    ~Sort() { delete[] a; }
};

int main()
{
    int n = 0;
    cin >> n;
    Sort<int> s(n);
    s.rank_sort();
    s.output();
}