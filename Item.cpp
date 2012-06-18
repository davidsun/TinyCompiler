#include <stdio.h>

#include "Item.h"

Item::Item(char left_side, const string &right_side, int position) : left_side(left_side), right_side(right_side), position(position){
}

Item::Item(const Item &item) : left_side(item.left_side), right_side(item.right_side), position(item.position){
}

Item &Item::operator = (const Item &item){
    left_side = item.left_side;
    right_side = item.right_side;
    position = item.position;
    return *this;
}

bool Item::operator == (const Item &item) const{
    return (left_side == item.left_side && right_side == item.right_side && position == item.position);
}

void Item::print() const{
    printf("%c -> %s, position=%d\n", left_side, right_side.c_str(), position);
}
