#include "bits/stdc++.h"

template <class T>
class stack
{
    int stackTop;
    int arrayLength;
    T *stackList;

public:
    stack();
    stack(int initialCapacity);
    ~stack() { delete[] stackList; }

    bool empty() { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    T top() const
    {
        if (stackTop == -1)
            exit(-1);
        return stackList[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
            exit(-1);
        stackList[stackTop--].~T();
    }
    void push(const T &theElement);
};

template <class T>
stack<T>::stack()
{
    arrayLength = 100000;
    stackList = new T[arrayLength];
    stackTop = -1;
}
template <class T>
stack<T>::stack(int initialCapacity)
{
    arrayLength = initialCapacity;
    stackList = new T[arrayLength];
    stackTop = -1;
}
template <class T>
void stack<T>::push(const T &theElement)
{
    if (stackTop == arrayLength - 1)
    {
        T *temp = new T[arrayLength * 2];
        std::copy(stackList, stackList + arrayLength, temp);
        delete[] stackList;
        stackList = temp;
        arrayLength *= 2;
    }
    stackList[++stackTop] = theElement;
}

bool IsPop(char a, char b)
{
    if (b == '(')
        return false;
    if (a == '*' || a == '/')
    {
        if (b == '+' || b == '-')
            return false;
        else
            return true;
    }
    return true;
}

std::string infixtosuffix(std::string src)
{
    std::string ans = "";
    stack<char> symbol;
    size_t i = 0;
    while (i < src.length())
    {
        if (isdigit(src[i]))
        {
            ans += src[i];
            if (!isdigit(src[i + 1]))
                ans += " ";
            ++i;
            continue;
        }
        switch (src[i])
        {
        case ' ':
            ++i;
            break;
        case '(':
            symbol.push(src[i]);
            ++i;
            break;
        case ')':
            while (symbol.top() != '(')
            {
                ans += symbol.top();
                ans += ' ';
                symbol.pop();
            }
            symbol.pop();
            ++i;
            break;

        case '+':
        case '-':
        case '*':
        case '/':
            if (symbol.empty())
            {
                symbol.push(src[i]);
                ++i;
            }
            else
            {
                if (IsPop(src[i], symbol.top()))
                {
                    ans += symbol.top();
                    ans += ' ';
                    symbol.pop();
                    break;
                }
                else
                {
                    symbol.push(src[i]);
                    ++i;
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
    while (!symbol.empty())
    {
        ans += symbol.top();
        ans += " ";
        symbol.pop();
    }

    return ans;
}

double calculate(std::string suf)
{
    stack<double> num;
    size_t i = 0;
    double ans = 0;
    int temp = 0;
    while (i < suf.length())
    {
        if (suf[i] == ' ')
        {
            ++i;
            continue;
        }
        else if (isdigit(suf[i]))
        {
            if (isdigit(suf[i + 1]))
            {
                temp += suf[i] - '0';
                temp *= 10;
            }
            else
            {
                temp += suf[i] - '0';
                num.push(temp);
                temp = 0;
            }
            ++i;
            continue;
        }
        else
        {
            if (num.size() < 2)
                exit(-1);
            double a = num.top();
            num.pop();
            double b = num.top();
            num.pop();
            switch (suf[i])
            {
            case '+':
                num.push(a + b);
                break;
            case '-':
                num.push(b - a);
                break;
            case '*':
                num.push(a * b);
                break;
            case '/':
                num.push(b / a);
                break;
            default:
                break;
            }
            ++i;
        }
    }

    ans = num.top();
    return ans;
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    while (n--)
    {
        std::string s;
        std::cin >> s;
        std::cout << std::setprecision(2) << calculate(infixtosuffix(s)) << std::endl;
    }
}