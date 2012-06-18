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
