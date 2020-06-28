#include "Source.h"

void printBoolList(list<bool> bList)
{
    cout << "[";
    for (list<bool>::iterator it = bList.begin(); it != bList.end();)
    {
        cout << *it;

        ++it;

        if (it != bList.end())
        {
            cout << ",";
        }
    }
    cout << "]";
}

int bListToInt(list<bool> bList) //Recursive binary calculation 1 + 2 *(0 + 2 *(...))
{
    if (bList.size() > 1)
    {
        bool b = bList.back();
        bList.pop_back();
        return b + 2 * (bListToInt(bList));
    }
    return bList.back();
}

list<bool> IntTobList(int integer)
{
    list<bool> bList;
    while (integer > 0)
    {
        bList.push_front(integer % 2);
        integer = integer / 2;
    }

    return bList;
}