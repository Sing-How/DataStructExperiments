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

template <class T>
class linkedBinaryTree
{
    binaryTreeNode<T> *root;
    binaryTreeNode<T> **pp; //指向第i个结点的指针
    int tot;
    int *treeSize;
    int *treeheight;

public:
    linkedBinaryTree(int n)
    {
        pp = new binaryTreeNode<T> *[n + 1];
        treeSize = new int[n + 1];
        treeheight = new int[n + 1];
        tot = n;
        for (int i = 1; i <= n; ++i)
        {
            pp[i] = new binaryTreeNode<T>(i);
            treeSize[i] = -1;
            treeheight[i] = -1;
        }
        root = pp[1];
    }

    void input()
    {
        for (int i = 1; i <= tot; ++i)
        {
            int a, b;
            std::cin >> a >> b;
            if (a == -1)
                pp[i]->leftChild = NULL;
            else
                pp[i]->leftChild = pp[a];
            if (b == -1)
                pp[i]->rightChild = NULL;
            else
                pp[i]->rightChild = pp[b];
        }
    }

    void levelOrder()
    {
        std::queue<binaryTreeNode<T> *> q;
        binaryTreeNode<T> *t = root;
        while (t != NULL)
        {
            std::cout << t->element << ' ';
            if (t->leftChild != NULL)
                q.push(t->leftChild);
            if (t->rightChild != NULL)
                q.push(t->rightChild);

            if (q.empty())
            {
                std::cout << std::endl;
                return;
            }

            t = q.front();
            q.pop();
        }
        std::cout << std::endl;
    }

    int heightcalcu(int i)
    {
        int lh = 0, rh = 0;
        if (pp[i]->leftChild != NULL)
            lh = heightcalcu(pp[i]->leftChild->element);
        if (pp[i]->rightChild != NULL)
            rh = heightcalcu(pp[i]->rightChild->element);
        treeheight[i] = std::max(lh, rh) + 1;
        return treeheight[i];
    }

    int numcalcu(int i)
    {
        int lh = 0, rh = 0;
        if (pp[i]->leftChild != NULL)
            lh = numcalcu(pp[i]->leftChild->element);
        if (pp[i]->rightChild != NULL)
            rh = numcalcu(pp[i]->rightChild->element);
        treeSize[i] = lh + rh + 1;
        return treeSize[i];
    }

    void output()
    {
        for (int i = 1; i <= tot; ++i)
            std::cout << treeSize[i] << ' ';
        std::cout << '\n';
        for (int i = 1; i <= tot; ++i)
            std::cout << treeheight[i] << ' ';
        std::cout << '\n';
    }
};

int main()
{
    int n;
    std::cin >> n;
    linkedBinaryTree<int> B(n);
    B.input();
    B.levelOrder();
    B.heightcalcu(1);
    B.numcalcu(1);
    B.output();
}