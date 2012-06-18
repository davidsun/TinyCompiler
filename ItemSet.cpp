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

#include <stdio.h>

#include "ItemSet.h"

ItemSet::ItemSet(){
}

ItemSet::ItemSet(const ItemSet &itemSet) : _items(itemSet._items){
}

ItemSet::ItemSet(const vector <Item> &items) : _items(items){
}

ItemSet &ItemSet::operator = (const ItemSet &itemSet){
    _items = itemSet._items;
    return *this;
}

ItemSet ItemSet::advance(char c, const vector <Item> &rules) const{
    ItemSet ret;
    for (int i = 0; i < _items.size(); i ++){
        const Item &item = _items[i];
        if (item.position < item.right_side.size() && item.right_side[item.position] == c)
            ret.addItem(Item(item.left_side, item.right_side, item.position + 1));
    }
    for (int i = 0; i < ret.getItems().size(); i ++){
        for (int j = 0; j < rules.size(); j ++){
            const Item &item = ret.getItems()[i];
            const Item &rule = rules[j];
            if (item.position < item.right_side.size() && item.right_side[item.position] == rule.left_side)
                ret.addItem(Item(rule.left_side, rule.right_side, 0));
        }
    }
    return ret;
}

bool ItemSet::operator == (const ItemSet &itemSet) const{
    if (_items.size() != itemSet._items.size()) return false;
    int found = 0;
    for (int i = 0; i < _items.size(); i ++){
        for (int j = 0; j < itemSet._items.size(); j ++){
            if (_items[i] == itemSet._items[j]){
                found ++;
                break;
            }
        }
    }
    return found == _items.size();
}

void ItemSet::addItem(const Item &item){
    for (int i = 0; i < _items.size(); i ++)
        if (_items[i] == item) return;
    _items.push_back(item);
}

const vector <Item> &ItemSet::getItems() const{
    return _items;
}

void ItemSet::print() const{
    for (int i = 0; i < _items.size(); i ++) _items[i].print();
}
