/* Copyright (C) 
 * 2012 - Zheng Sun (http://pursuer.me)
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

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
