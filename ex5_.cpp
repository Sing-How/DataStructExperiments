#include <iostream>
const int maxsize = 99999;

using namespace std;

struct Matrixunion
{
    int row, col, value;
    Matrixunion &operator=(Matrixunion &x)
    {
        row = x.row;
        col = x.col;
        value = x.value;
        return *this;
    }
};

class sparseMatrix
{
    friend ostream &operator<<(ostream &out, sparseMatrix &a);

public:
    sparseMatrix(int r, int c);
    ~sparseMatrix()
    {
        delete[] element;
    }
    sparseMatrix &operator=(sparseMatrix &a);
    void add(sparseMatrix &a);
    void transpose();
    void initial(int r, int c);
    void inputAelement(int x, int y, int z);
    void insert(int theIndex, const Matrixunion &theElement);
    void multiply(sparseMatrix &a);
    void output();

private:
    int Rows, Cols, Terms;
    Matrixunion *element;
    int maxSize;
};

void sparseMatrix::inputAelement(int x, int y, int z)
{
    Matrixunion New;
    New.row = x;
    New.col = y;
    New.value = z;
    element[Terms] = New;
    Terms++;
}

void sparseMatrix::multiply(sparseMatrix &a)
{
    if (Cols != a.Rows)
    {
        *this = a;
        cout << -1 << endl;
    }

    else
    {
        sparseMatrix b(Rows, a.Cols);
        int sizeofrow[10000];
        int nextofrow[10000];
        int theanswer[10000];
        for (int i = 1; i <= a.Rows; i++)
            sizeofrow[i] = 0;
        for (int i = 0; i < a.Terms; i++)
        {
            if (a.element[i].value != 0)
            {
                sizeofrow[a.element[i].row]++;
            }
        }
        nextofrow[1] = 0;
        for (int i = 2; i <= a.Terms; i++)
            nextofrow[i] = nextofrow[i - 1] + sizeofrow[i - 1];
        int p = 0;
        for (int i = 1; i <= Rows && p < Terms; i++)
        {
            for (int j = 1; j <= a.Cols; j++)
                theanswer[j] = 0;
            while (p < Terms && element[p].row == i)
            {
                int t = element[p].col;
                if (sizeofrow[t] != 0)
                {
                    for (int q = nextofrow[t]; q < nextofrow[t] + sizeofrow[t]; q++)
                    {
                        theanswer[a.element[q].col] += element[p].value * a.element[q].value;
                    }
                }
                p++;
            }
            for (int k = 1; k <= a.Cols; k++)
            {
                if (theanswer[k] != 0)
                {
                    b.element[b.Terms].value = theanswer[k];
                    b.element[b.Terms].row = i;
                    b.element[b.Terms].col = k;
                    b.Terms++;
                }
            }
        }
        *this = b;
    }
}

void sparseMatrix::transpose()
{
    sparseMatrix b(Cols, Rows);
    b.Terms = Terms;
    b.Cols = Rows;
    b.Rows = Cols;
    int *colSize = new int[Cols + 1];
    int *rowNext = new int[Cols + 1];

    for (int i = 1; i <= Cols; i++)
        colSize[i] = 0;
    for (int i = 0; i < Terms; i++)
        colSize[element[i].col]++;

    rowNext[1] = 0;
    for (int i = 2; i <= Cols; i++)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    for (int i = 0; i < Terms; i++)
    {
        int j = rowNext[element[i].col]++;
        b.element[j].row = element[i].col;
        b.element[j].col = element[i].row;
        b.element[j].value = element[i].value;
    }
    *this = b;
}

void sparseMatrix::initial(int r, int c)
{
    Rows = r;
    Cols = c;
    Terms = 0;
    int flag = 0;
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Cols; j++)
        {
            int b;
            cin >> b;
            if (b != 0)
            {
                element[flag].row = i + 1;
                element[flag].col = j + 1;
                element[flag].value = b;
                Terms++;
                flag++;
            }
        }
    }
}

sparseMatrix::sparseMatrix(int r, int c)
{
    element = new Matrixunion[maxsize];
    Rows = r;
    Cols = c;
    Terms = 0;
}

sparseMatrix &sparseMatrix::operator=(sparseMatrix &a)
{
    Rows = a.Rows;
    Cols = a.Cols;
    Terms = a.Terms;
    maxSize = a.maxSize;
    for (int i = 0; i < Terms; i++)
        element[i] = a.element[i];
    return *this;
}

ostream &operator<<(ostream &out, sparseMatrix &a)
{
    cout << a.Rows << " " << a.Cols << endl;
    for (int i = 1; i < a.Rows + 1; i++)
    {
        for (int j = 1; j < a.Cols + 1; j++)
        {
            int flag = 0;
            for (int k = 0; k < a.Terms; k++)
            {
                if (a.element[k].row == i && a.element[k].col == j)
                {
                    cout << a.element[k].value << " ";
                    flag++;
                }
            }
            if (flag == 0)
                cout << 0 << " ";
        }
        cout << endl;
    }
    return out;
}

void sparseMatrix::output()
{
    int i, j, k = 0;
    cout << Rows << " " << Cols << endl;
    for (i = 0; i < Rows; i++)
    {
        for (j = 0; j < Cols; j++)
        {
            if (k < Terms && element[k].row == i + 1 && element[k].col == j + 1)
            {
                cout << element[k].value << " ";
                k++;
            }
            else
            {
                cout << 0 << " ";
            }
        }
        cout << endl;
    }
}

void sparseMatrix::insert(int theIndex, const Matrixunion &theElement)
{

    copy_backward(element + theIndex, element + Terms,
                  element + Terms + 1);

    element[theIndex].col = theElement.col;
    element[theIndex].row = theElement.row;
    element[theIndex].value = theElement.value;

    Terms++;
}

void sparseMatrix::add(sparseMatrix &b)
{
    sparseMatrix c(Rows, Cols);
    if (b.Cols != Cols || b.Rows != Rows)
    {
        *this = b;
        cout << -1 << endl;
        return;
    }
    int cSize = 0;
    int it = 0;
    int ib = 0;
    int itEnd = Terms;
    int ibEnd = b.Terms;
    while (it != itEnd && ib != ibEnd)
    {

        int tIndex = element[it].row * Cols + element[it].col;
        int bIndex = b.element[ib].row * Cols + b.element[ib].col;

        if (tIndex < bIndex)
        {
            //c.element[cSize++] = element[it];
            c.insert(cSize++, element[it]);
            it++;
        }
        else
        {
            if (tIndex == bIndex)
            {
                if (element[it].value + b.element[ib].value != 0)
                {
                    Matrixunion mTerm;
                    mTerm.row = element[it].row;
                    mTerm.col = element[it].col;
                    mTerm.value = element[it].value + b.element[ib].value;
                    //c.element[cSize++] = mTerm;
                    c.insert(cSize++, mTerm);
                }

                it++;
                ib++;
            }
            else
            {
                //c.element[cSize++] = b.element[ib];
                c.insert(cSize++, b.element[ib]);
                ib++;
            }
        }
    }

    for (; it != itEnd; it++)
        //  c.element[cSize++] = element[it];
        c.insert(cSize++, element[it]);
    for (; ib != ibEnd; ib++)
        //   c.element[cSize++] = b.element[ib];
        c.insert(cSize++, b.element[ib]);

    *this = c;
}

int main()
{
    sparseMatrix x(0, 0);
    int w;
    int r, c, t, trans;
    cin >> w;
    for (int i = 0; i < w; i++)
    {
        cin >> trans;
        if (trans == 1)
        {
            cin >> r >> c;
            x.initial(r, c);
        }
        else if (trans == 2)
        {
            cin >> r >> c;
            cin >> t;
            sparseMatrix y(r, c);
            for (int i = 0; i < t; i++)
            {
                int r1, c1, t1;
                cin >> r1 >> c1 >> t1;
                y.inputAelement(r1, c1, t1);
            }
            x.multiply(y);
        }
        else if (trans == 3)
        {
            cin >> r >> c;
            cin >> t;
            sparseMatrix y1(r, c);
            for (int i = 0; i < t; i++)
            {
                int r1, c1, t1;
                cin >> r1 >> c1 >> t1;
                y1.inputAelement(r1, c1, t1);
            }
            x.add(y1);
        }
        else if (trans == 4)
        {
            x.output();
        }
        else if (trans == 5)
        {
            x.transpose();
        }
    }
}
