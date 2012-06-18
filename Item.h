#ifndef _ITEM_H
#define _ITEM_H

#include <string>

using namespace std;

class Item{
    public:
        Item(char left_side, const string &right_side, int position);
        Item(const Item &item);

        Item &operator = (const Item &item);
        bool operator == (const Item &item) const;
        
        void print() const;

        char left_side;
        string right_side;
        int position;
};

#endif
