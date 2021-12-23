#include "bits/stdc++.h"
using namespace std;

struct Person
{
    string name, tel_num, doom_id, class_id;
};

template <class T>
class arrayList
{
protected:
    T *element;
    int arrayLength;
    int listSize;

public:
    arrayList()
    {
        arrayLength = 20010;
        element = new T[arrayLength];
        listSize = 0;
    }
    arrayList(int arraylength);
    ~arrayList() { delete[] element; }

    //ADT
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    void insert(const T &theElement);
    void remove(string &thename);
    void edit(string &thename, char &item, string &newitem);
    void checkName(string &thename) const;
    void outputDoom(string &thedoom) const;
};

template <class T>
arrayList<T>::arrayList(int arraylength)
{
    // if (arraylength < 1)
    // {
    //     ostringstream s;
    //     s << "initial capacity = " << arraylength << ", but must be > 1";
    //     throw illeagallength(s.str());
    // }
    arrayLength = 20010;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
void arrayList<T>::insert(const T &theElement)
{
    // if (arrayLength == listSize)
    // {
    //     T *temp = element;
    //     element = new T[arrayLength + 10];
    //     arrayLength += 10;
    //     copy(temp, temp + arrayLength, element);
    //     delete[] temp;
    // }
    element[listSize].name = theElement.name;
    element[listSize].tel_num = theElement.tel_num;
    element[listSize].class_id = theElement.class_id;
    element[listSize].doom_id = theElement.doom_id;

    ++listSize;
}

template <class T>
void arrayList<T>::remove(string &thename)
{
    for (int i = 0; i < listSize; ++i)
    {
        if (element[i].name == thename)
        {
            copy(element + i + 1, element + listSize, element + i);
            --listSize;
            return;
        }
    }
}

template <class T>
void arrayList<T>::edit(string &thename, char &item, string &newitem)
{
    for (int i = 0; i < listSize; ++i)
    {
        if (element[i].name == thename)
        {
            switch (item)
            {
            case 1:
                element[i].tel_num = newitem;
                break;
            case 2:
                element[i].class_id = newitem;
                break;
            case 3:
                element[i].doom_id = newitem;
                break;
            default:
                break;
            }
            return;
        }
    }
}

template <class T>
void arrayList<T>::checkName(string &thename) const
{
    for (int i = 0; i < listSize; ++i)
    {
        if (element[i].name == thename)
        {
            cout << 1 << endl;
            return;
        }
    }
    cout << 0 << endl;
}

template <class T>
void arrayList<T>::outputDoom(string &theclass) const
{
    int ans = 0;
    for (int i = 0; i < listSize; ++i)
    {
        if (element[i].class_id == theclass)
            ans ^= atoi(element[i].doom_id.c_str());
    }
    cout << ans << endl;
}

int main()
{
    arrayList<Person> p;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int k;
        cin >> k;
        switch (k)
        {
        case 0:
        {
            Person newone;
            cin >> newone.name >> newone.tel_num >> newone.class_id >> newone.doom_id;
            p.insert(newone);
        }
        break;
        case 1:
        {
            string thename;
            cin >> thename;
            p.remove(thename);
        }
        break;
        case 2:
        {
            string thename;
            char item;
            string newitem;
            cin >> thename >> item >> newitem;
            p.edit(thename, item, newitem);
        }
        break;
        case 3:
        {
            string thename;
            cin >> thename;
            p.checkName(thename);
        }
        break;
        case 4:
        {
            string theclass;
            cin >> theclass;
            p.outputDoom(theclass);
        }
        break;
        }
    }
}