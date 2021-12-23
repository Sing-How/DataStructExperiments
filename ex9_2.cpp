#include "bits/stdc++.h"

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;
    int No;

    binaryTreeNode() { leftChild = rightChild = NULL; }
    binaryTreeNode(const T &theElement)
    {
        element = theElement;
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T &theElement, const binaryTreeNode *theleftChild, const binaryTreeNode *therightChild)
    {
        element = theElement;
        leftChild = theleftChild;
        rightChild = therightChild;
    }
};

binaryTreeNode<int> *f(int *pre, int *in, int length)
{
    if (length == 0)
        return NULL;
    binaryTreeNode<int> *node = new binaryTreeNode<int>(*pre);
    int i;
    for (i = 0; i < length; ++i)
    {
        if (in[i] == *pre)
            break;
    }

    node->leftChild = f(pre + 1, in, i);
    node->rightChild = f(pre + i + 1, in + i + 1, length - i - 1);

    std::cout << node->element << ' ';
    return node;
}

int main()
{
    int n;
    int *pre, *in;
    std::cin >> n;
    pre = new int[n];
    in = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> pre[i];
    for (int i = 0; i < n; ++i)
        std::cin >> in[i];
    f(pre, in, n);
}