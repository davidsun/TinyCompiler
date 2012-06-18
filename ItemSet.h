#ifndef _ITEMSET_H
#define _ITEMSET_H

#include <vector>
#include <string>

#include "Item.h"

using namespace std;

class ItemSet{
    public:
        ItemSet();
        ItemSet(const ItemSet &itemSet);
        ItemSet(const vector <Item> &items);

        ItemSet &operator = (const ItemSet &itemSet);
        bool operator == (const ItemSet &itemSet) const;

        ItemSet advance(char c, const vector <Item> &rules) const;
        void addItem(const Item &item);
        const vector <Item> &getItems() const;
        void print() const;
    
    private:
        vector <Item> _items;
};

#endif
