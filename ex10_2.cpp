#include <iostream>
#include <string>
#include <queue>
using namespace std;
template <class T>

struct binaryTreeNode
{
    T element;
    binaryTreeNode *leftchild;
    binaryTreeNode *rightchild;
    binaryTreeNode()
    {
        element = 0;
        leftchild = NULL;
        rightchild = NULL;
    }
    binaryTreeNode(const T &theelement)
    {
        element = theelement;
        leftchild = NULL;
        rightchild = NULL;
    }
    binaryTreeNode(const T &theelement, binaryTreeNode *l, binaryTreeNode *r)
    {
        element = theelement;
        leftchild = l;
        rightchild = r;
    }
};

template <class T>

class minheap
{
private:
    int size;
    T *heap;

public:
    minheap()
    {
        heap = new T[7001];
        size = 0;
    }

    int fix(int index)
    {
        if (index * 2 > size)
            return -1;
        if (index * 2 + 1 > size)
        {
            if (heap[index * 2]->element < heap[index]->element)
            {
                T temp = heap[index];
                heap[index] = heap[index * 2];
                heap[index * 2] = temp;
                return index * 2;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            if (heap[index]->element < heap[index * 2]->element && heap[index]->element < heap[index * 2 + 1]->element)
            {
                return -1;
            }
            else
            {
                if (heap[index * 2 + 1]->element < heap[index * 2]->element)
                {
                    T temp = heap[index];
                    heap[index] = heap[index * 2 + 1];
                    heap[index * 2 + 1] = temp;
                    return index * 2 + 1;
                }
                else
                {
                    T temp = heap[index];
                    heap[index] = heap[index * 2];
                    heap[index * 2] = temp;
                    return index * 2;
                }
            }
        }
    }
    T &top()
    {
        return heap[1];
    }

    void push(const T &value)
    {

        heap[++size] = value;
        int p = size;
        while (p != 1)
        {
            int x = fix(p / 2);
            if (x == -1)
                break;
            p = p / 2;
        }
    }
    void pop()
    {
        if (size == 0)
            return;
        heap[1] = heap[size--];
        int p = 1;
        while (1)
        {
            p = fix(p);
            if (p == -1)
                break;
        }
    }
};
template <class T>

class binaryTree
{
private:
    int num;

public:
    binaryTreeNode<T> *root;
    binaryTree(binaryTreeNode<T> *r)
    {
        root = r;
    }

    int computehuffman()
    {
        if (root == NULL)
            return 0;
        int ans = 0;
        precompute(root, 0, ans);
        return ans;
    }
    void precompute(binaryTreeNode<T> *t, int h, int &ans)
    {

        if (t->leftchild == NULL && t->rightchild == NULL)
        {
            ans += h * (t->element);
            return;
        }
        if (t->leftchild != NULL)
        {
            precompute(t->leftchild, h + 1, ans);
        }
        if (t->rightchild != NULL)
        {
            precompute(t->rightchild, h + 1, ans);
        }
    }
};

int main()
{
    int f[26] = {0};
    minheap<binaryTreeNode<int> *> p;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        f[s[i] - 97]++;
    }
    binaryTreeNode<int> **node = new binaryTreeNode<int> *[26];
    for (int i = 0; i < 26; i++)
    {
        node[i] = new binaryTreeNode<int>;
    }
    int num = 0;
    for (int i = 0; i < 26; i++)
    {
        node[i]->element = f[i];
        if (node[i]->element != 0)
        {
            p.push(node[i]);
            num++;
        }
    }

    for (int i = 1; i <= num - 1; i++)
    {
        binaryTreeNode<int> *x = p.top();
        int xe = p.top()->element;
        p.pop();
        binaryTreeNode<int> *y = p.top();
        int ye = p.top()->element;
        p.pop();
        binaryTreeNode<int> *t = new binaryTreeNode<int>(xe + ye, x, y);
        p.push(t);
    }
    binaryTree<int> tree(p.top());
    cout << tree.computehuffman();
}