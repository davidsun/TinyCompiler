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

#ifndef _LRANALYTICS_H
#define _LRANALYTICS_H

#include <vector>
#include <string>

#include "Item.h"
#include "ItemSet.h"

using namespace std;

class LRAnalytics{
    public:
        const static char END_LETTER;
        const static char INPUT_END_LETTER;
        const static char START_LETTER;

        LRAnalytics();
        LRAnalytics(const LRAnalytics &lr_analytics);

        void addRule(char left_side, const string &right_side);
        vector <ItemSet> genStates() const;
        string getNonTerminals() const;
        const vector <Item> &getRules() const;
        string getTerminals() const;
        vector <vector <string> > genTable() const;
        vector <int> parse(string str, bool quiet = true) const;

    private:
        string _letters;
        vector <Item> _rules;
};

#endif
