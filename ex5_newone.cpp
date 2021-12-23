#include "bits/stdc++.h"
using namespace std;

struct MatrixTerm
{
    int row, col, value;
    MatrixTerm() {}
    MatrixTerm(int theRow, int theCol, int theValue) : row(theRow), col(theCol), value(theValue) {}
    MatrixTerm &operator=(MatrixTerm &x)
    {
        row = x.row;
        col = x.col;
        value = x.value;
        return *this;
    }
};

class spraseMatrix
{
    int rowCount, colCount, termCount;
    const int maxsize = 100000;
    MatrixTerm *element;

public:
    spraseMatrix() { element = new MatrixTerm[maxsize]; }
    spraseMatrix(int theRow, int theCol) : rowCount(theRow), colCount(theCol), termCount(0) { element = new MatrixTerm[maxsize]; }
    ~spraseMatrix() { delete[] element; }

    spraseMatrix &operator=(spraseMatrix &x);
    void insert(int theIndex, const MatrixTerm &theElement);
    void add(spraseMatrix &a);
    void transpose();
    void reset(int newRow, int newCol);
    // void input(int x, int y, int value);
    void multi(spraseMatrix &a);
    void output();
};

spraseMatrix &spraseMatrix::operator=(spraseMatrix &x)
{
    rowCount = x.rowCount;
    colCount = x.colCount;
    termCount = x.termCount;
    delete[] element;
    element = new MatrixTerm[maxsize];
    for (int i = 0; i < termCount; ++i)
        element[i] = x.element[i];
    return *this;
}

void spraseMatrix::insert(int theIndex, const MatrixTerm &theElement)
{
    copy_backward(element + theIndex, element + termCount, element + termCount + 1);

    element[theIndex].col = theElement.col;
    element[theIndex].row = theElement.row;
    element[theIndex].value = theElement.value;

    termCount++;
}

void spraseMatrix::add(spraseMatrix &a)
{
    if (rowCount != a.rowCount or colCount != a.colCount)
    {
        *this = a;
        cout << -1 << endl;
        return;
    }
    spraseMatrix ans(rowCount, colCount);
    int cntans = 0;
    int it = 0, ia = 0, itEnd = termCount, iaEnd = a.termCount;
    while (it != itEnd and ia != iaEnd)
    {
        int tIndex = element[it].row * colCount + element[it].col;
        int aIndex = a.element[ia].row * colCount + a.element[ia].col;

        if (tIndex < aIndex)
        {
            ans.insert(cntans++, element[it]);
            ++it;
        }
        else
        {
            if (tIndex > aIndex)
            {
                ans.insert(cntans++, a.element[ia]);
                ++ia;
            }
            else
            {
                if (element[it].value + a.element[ia].value != 0)
                {
                    MatrixTerm mt(element[it].row, element[it].col, element[it].value + a.element[ia].value);
                    ans.insert(cntans++, mt);
                }
                it++;
                ia++;
            }
        }
    }
    while (it != itEnd)
        ans.insert(cntans++, element[it++]);
    while (ia != iaEnd)
        ans.insert(cntans++, a.element[ia++]);

    *this = ans;
}

void spraseMatrix::transpose()
{
    spraseMatrix ans(colCount, rowCount);
    ans.termCount = termCount;

    int *colSize = new int[colCount + 1];
    int *firstPo = new int[colCount + 1]; //每一列首个非零元素在答案数组中的索引位置

    for (int i = 1; i < colCount; ++i)
        colSize[i] = 0;
    for (int i = 0; i < termCount; ++i)
        colSize[element[i].col]++;

    firstPo[1] = 0;
    for (int i = 2; i <= colCount; ++i)
        firstPo[i] = firstPo[i - 1] + colSize[i - 1];

    for (int i = 0; i < termCount; ++i)
    {
        int j = firstPo[element[i].col]++;
        ans.element[j].row = element[i].col;
        ans.element[j].col = element[i].row;
        ans.element[j].value = element[i].value;
    }
    *this = ans;
}

void spraseMatrix::reset(int newRow, int newCol)
{
    delete[] element;
    element = new MatrixTerm[maxsize];
    rowCount = newRow;
    colCount = newCol;
    termCount = 0;
    int cnt = 0;
    for (int i = 1; i <= rowCount; ++i)
    {
        for (int j = 1; j <= colCount; ++j)
        {
            int temp = 0;
            cin >> temp;
            if (temp)
            {
                MatrixTerm mt(i, j, temp);
                insert(cnt++, mt);
            }
        }
    }
}

void spraseMatrix::multi(spraseMatrix &a)
{
    if (colCount != a.rowCount)
    {
        *this = a;
        cout << -1 << endl;
        return;
    }

    spraseMatrix ans(rowCount, a.colCount);
    int sizeofrow[10000];
    int nextofrow[10000]; //每一列首个非零元素在数组中的索引位置
    int theanswer[10000];
    for (int i = 1; i <= a.rowCount; ++i)
        sizeofrow[i] = 0;
    for (int i = 0; i < a.termCount; ++i)
        sizeofrow[a.element[i].row]++;

    nextofrow[1] = 0;
    for (int i = 2; i <= a.termCount; ++i)
        nextofrow[i] = sizeofrow[i - 1] + nextofrow[i - 1];

    int p = 0;
    for (int i = 1; i <= rowCount and p < termCount; ++i)
    {
        for (int j = 1; j <= a.colCount; ++j)
            theanswer[j] = 0;
        while (p < termCount and element[p].row == i)
        {
            int t = element[p].col;
            if (sizeofrow[t])
            {
                for (int q = nextofrow[t]; q < nextofrow[t] + sizeofrow[t]; ++q)
                    theanswer[a.element[q].col] += element[p].value * a.element[q].value;
            }
            ++p;
        }

        for (int k = 1; k <= a.colCount; ++k)
        {
            if (theanswer[k])
            {
                ans.element[ans.termCount].value = theanswer[k];
                ans.element[ans.termCount].row = i;
                ans.element[ans.termCount].col = k;
                ans.termCount++;
            }
        }
    }
    *this = ans;
}

void spraseMatrix::output()
{
    int cnt = 0;
    cout << rowCount << ' ' << colCount << endl;
    for (int i = 1; i <= rowCount; ++i)
    {
        for (int j = 1; j <= colCount; ++j)
        {
            if (cnt < termCount and element[cnt].row == i and element[cnt].col == j)
                cout << element[cnt++].value << ' ';
            else
                cout << 0 << ' ';
        }
        cout << endl;
    }
}

int main()
{
    spraseMatrix P;
    int w;
    cin >> w;
    while (w--)
    {
        int ctrl;
        cin >> ctrl;
        switch (ctrl)
        {
        case 1:
        {
            int r, c;
            cin >> r >> c;
            P.reset(r, c);
        }
        break;
        case 2:
        {
            int r, c, t;
            cin >> r >> c >> t;
            int cnt = 0;
            spraseMatrix Q(r, c);
            while (t--)
            {
                int r1, c1, v1;
                cin >> r1 >> c1 >> v1;
                MatrixTerm mt(r1, c1, v1);
                Q.insert(cnt++, mt);
            }
            P.multi(Q);
        }
        break;
        case 3:
        {
            int r, c, t;
            cin >> r >> c >> t;
            int cnt = 0;
            spraseMatrix Q(r, c);
            while (t--)
            {
                int r1, c1, v1;
                cin >> r1 >> c1 >> v1;
                MatrixTerm mt(r1, c1, v1);
                Q.insert(cnt++, mt);
            }
            P.add(Q);
        }
        break;
        case 4:
            P.output();
            break;
        case 5:
            P.transpose();
            break;
        default:
            break;
        }
    }
}