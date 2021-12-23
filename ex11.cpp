#include <iostream>
#include <queue>
#include <stack>
using namespace std;
template <class T>

struct binaryTreeNode
{
    T element;
    binaryTreeNode *leftchild;
    binaryTreeNode *rightchild;
    int leftsize;
    binaryTreeNode()
    {
        element = 0;
        leftchild = NULL;
        rightchild = NULL;
        leftsize = 0;
    }
    binaryTreeNode(const T &theelement)
    {
        element = theelement;
        leftchild = NULL;
        leftsize = 0;
        rightchild = NULL;
    }
    binaryTreeNode(const T &theelement, binaryTreeNode *l, binaryTreeNode *r)
    {
        element = theelement;
        leftchild = l;
        leftsize = 0;
        rightchild = r;
    }
};
template <class T>

class binarySearchTree
{
private:
    int size;
    binaryTreeNode<T> *root;

public:
    binarySearchTree()
    {
        size = 0;
        root = NULL;
    }
    int getsize()
    {
        return size;
    }
    void push(const T &value)
    {
        int ans = 0;
        stack<binaryTreeNode<T> *> s;
        if (root == NULL)
        {
            root = new binaryTreeNode<T>(value);
            size++;
            cout << 0 << endl;
            return;
        }
        binaryTreeNode<T> *p = root;
        while (1)
        {
            if (value > p->element)
            {
                ans = ans ^ p->element;
                if (p->rightchild == NULL)
                {
                    binaryTreeNode<T> *t = new binaryTreeNode<T>(value);
                    p->rightchild = t;
                    break;
                }
                else
                {
                    p = p->rightchild;
                }
            }
            else if (value < p->element)
            {
                s.push(p);
                ans = ans ^ p->element;
                if (p->leftchild == NULL)
                {
                    binaryTreeNode<T> *t = new binaryTreeNode<T>(value);
                    p->leftchild = t;
                    break;
                }
                else
                {
                    p = p->leftchild;
                }
            }
            else if (value == p->element)
            {
                cout << 0 << endl;
                return;
            }
        }

        while (!s.empty())
        {
            binaryTreeNode<T> *temp = s.top();
            temp->leftsize++;
            s.pop();
        }
        cout << ans << endl;
        size++;
    }
    void search(const T &value)
    {
        int ans = 0;
        binaryTreeNode<T> *p = root;
        while (p != NULL && p->element != value)
        {
            ans = ans ^ p->element;
            if (p->element > value)
            {
                p = p->leftchild;
                continue;
            }
            if (p->element < value)
            {
                p = p->rightchild;
            }
        }
        if (p == NULL)
        {
            cout << 0 << endl;
        }
        else
        {
            ans = ans ^ p->element;
            cout << ans << endl;
        }
    }
    void delete_Node(binaryTreeNode<T> *d, binaryTreeNode<T> *pd)
    {
        binaryTreeNode<T> *child = NULL;
        if (d->leftchild != NULL)
            child = d->leftchild;
        else
            child = d->rightchild;
        if (d == pd->leftchild)
        {
            pd->leftchild = child;
        }
        else
        {
            pd->rightchild = child;
        }
        delete d;
    }
    void erase_by_value(const T &value, bool output)
    {
        binaryTreeNode<T> *p = root;
        binaryTreeNode<T> *pp = NULL;
        stack<binaryTreeNode<T> *> s;
        int ans = 0;
        while (1)
        {
            if (p == NULL)
            {
                if (output)
                    cout << 0 << endl;
                return;
            }
            if (value == p->element)
            {
                ans = ans ^ p->element;
                break;
            }
            if (value > p->element)
            {
                ans = ans ^ p->element;+
                pp = p;
                p = p->rightchild;
            }
            else
            {
                s.push(p);
                ans = ans ^ p->element;
                pp = p;
                p = p->leftchild;
            }
        }
        while (!s.empty())
        {
            binaryTreeNode<T> *temp = s.top();
            temp->leftsize--;
            s.pop();
        }

        if (p == root)
        {
            if (p->leftchild == NULL && p->rightchild == NULL)
            {
                delete p;
                root = NULL;
            }
            else if (p->leftchild == NULL && p->rightchild != NULL)
            {
                root = p->rightchild;
                delete p;
                p = NULL;
            }
            else if (p->leftchild != NULL && p->rightchild == NULL)
            {
                root = p->leftchild;
                delete p;
                p = NULL;
            }
            else
            {
                binaryTreeNode<T> *right_min = p->rightchild;
                binaryTreeNode<T> *prm = p;
                while (right_min->leftchild != NULL)
                {
                    right_min->leftsize--;
                    prm = right_min;
                    right_min = right_min->leftchild;
                }
                p->element = right_min->element;
                delete_Node(right_min, prm);
            }
        }
        else
        {
            if (p->leftchild == NULL && p->rightchild == NULL)
            {
                if (p == pp->leftchild)
                    pp->leftchild = NULL;
                if (p == pp->rightchild)
                    pp->rightchild = NULL;
                p = NULL;
                delete p;
            }
            else if (p->leftchild == NULL && p->rightchild != NULL)
            {
                delete_Node(p, pp);
            }
            else if (p->leftchild != NULL && p->rightchild == NULL)
            {
                delete_Node(p, pp);
            }
            else
            {
                binaryTreeNode<T> *right_min = p->rightchild;
                binaryTreeNode<T> *prm = p;
                while (right_min->leftchild != NULL)
                {
                    right_min->leftsize--;
                    prm = right_min;
                    right_min = right_min->leftchild;
                }
                p->element = right_min->element;
                delete_Node(right_min, prm);
            }
        }

        size--;
        if (output)
            cout << ans << endl;
    }
    void erase_by_rank(int rank)
    {
        int sum = size;
        int ans = 0;
        if (rank > size || rank <= 0)
        {
            cout << 0 << endl;
            return;
        }
        binaryTreeNode<T> *p = root;
        while (1)
        {
            if (rank > p->leftsize + 1)
            {
                ans = ans ^ p->element;
                sum = sum - p->leftsize - 1;
                rank = rank - p->leftsize - 1;
                p = p->rightchild;
            }
            else if (rank == p->leftsize + 1)
            {
                ans = ans ^ p->element;
                cout << ans << endl;
                erase_by_value(p->element, false);
                return;
            }
            else if (rank < p->leftsize + 1)
            {
                ans = ans ^ p->element;
                sum = p->leftsize;
                p = p->leftchild;
            }
        }
    }
    void find_by_rank(int rank)
    {
        int sum = size;
        int ans = 0;
        if (rank > size || rank <= 0)
        {
            cout << 0 << endl;
            return;
        }
        binaryTreeNode<T> *p = root;
        while (1)
        {
            if (rank > p->leftsize + 1)
            {
                ans = ans ^ p->element;
                sum = sum - p->leftsize - 1;
                rank = rank - p->leftsize - 1;
                p = p->rightchild;
            }
            else if (rank == p->leftsize + 1)
            {
                ans = ans ^ p->element;
                cout << ans << endl;
                return;
            }
            else if (rank < p->leftsize + 1)
            {
                ans = ans ^ p->element;
                sum = p->leftsize;
                p = p->leftchild;
            }
        }
    }
};

int main()
{
    binarySearchTree<int> t;

    int m;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int k, b;
        cin >> k >> b;
        if (k == 0)
        {
            t.push(b);
        }
        if (k == 1)
        {
            t.search(b);
        }
        if (k == 2)
        {
            t.erase_by_value(b, true);
        }
        if (k == 3)
        {
            t.find_by_rank(b);
        }
        if (k == 4)
        {
            t.erase_by_rank(b);
        }
    }
}