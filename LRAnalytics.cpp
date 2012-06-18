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
#include <stack>
#include <map>

#include "LRAnalytics.h"
#include "Utils.h"
#include "Exception.h"

const char LRAnalytics::END_LETTER = 'E';
const char LRAnalytics::INPUT_END_LETTER = '$';
const char LRAnalytics::START_LETTER = 'S';

LRAnalytics::LRAnalytics(){
    addRule(START_LETTER, string() + END_LETTER);
    _letters += INPUT_END_LETTER;
}

LRAnalytics::LRAnalytics(const LRAnalytics &lr_analytics) : _letters(lr_analytics._letters), _rules(lr_analytics._rules){
}

void LRAnalytics::addRule(char left_side, const string &right_side){
    _rules.push_back(Item(left_side, right_side, 0));
    for (int i = 0; i < right_side.size(); i ++)
        if (std::string::npos == _letters.find(right_side[i])) _letters += right_side[i];
    if (std::string::npos == _letters.find(left_side)) _letters += left_side;
}

vector <ItemSet> LRAnalytics::genStates() const{
    vector <ItemSet> ret;
    ret.push_back(_rules);
    int cur = 0;
    while (cur < ret.size()){
        for (int i = 0; i < _letters.size(); i ++){
            const ItemSet &p = ret[cur]; 
            ItemSet newSet = p.advance(_letters[i], _rules);
            int j;
            for (j = 0; j < ret.size(); j ++)
                if (newSet == ret[j]) break; 
            if (newSet.getItems().size() > 0 && j == ret.size()) ret.push_back(newSet);
        }
        cur ++;
    }
    return ret;
}

string LRAnalytics::getNonTerminals() const{
    string ret;
    for (int i = 0; i < _rules.size(); i ++)
        if (std::string::npos == ret.find(_rules[i].left_side)) ret += _rules[i].left_side;
    return ret;
}

const vector <Item> &LRAnalytics::getRules() const{
    return _rules;
}

string LRAnalytics::getTerminals() const{
    string non = getNonTerminals();
    string ret;
    for (int i = 0; i < _letters.size(); i ++)
        if (std::string::npos == non.find(_letters[i])) ret += _letters[i];
    return ret;
}

vector <vector <string> > LRAnalytics::genTable() const{
    vector <ItemSet> states = genStates();
    vector <vector <string> > ret;
    ret.push_back(vector <string>());
    const string &str = getTerminals() + getNonTerminals();
    for (int i = 0; i < str.size(); i ++) ret[0].push_back(string() + str[i]);
    for (int i = 0; i < states.size(); i ++){
        vector <string> newJump;
        for (int j = 0; j < str.size(); j ++){
            ItemSet newSet = states[i].advance(str[j], _rules);
            if (newSet.getItems().size() > 0){
                for (int k = 0; k < states.size(); k ++){
                    if (states[k] == newSet){
                        newJump.push_back("s" + Utils::toString(k));
                        break;
                    }
                }
            }  else {
                newJump.push_back("");
            }
        }
        ret.push_back(newJump);
    }
    for (int i = 0; i < states.size(); i ++){
        const vector <Item> &items = states[i].getItems();
        int found = 0;
        for (int j = 0; j < items.size(); j ++){
            if (items[j].position != items[j].right_side.length()) continue;
            for (int k = 0; k < _rules.size(); k ++){
                if (items[j].left_side == _rules[k].left_side && items[j].right_side == _rules[k].right_side){
                    found ++;
                    if (k == 0){
                        for (int l = 0; l < ret[i + 1].size(); l ++)
                            if (str[l] == INPUT_END_LETTER) ret[i + 1][l] = "acc";
                    }  else {
                        /*
                         * Notice here, here r is added to all items in this row for convenience, but not to FOLLOW(state) in normal cases.
                         */
                        int t_size = getTerminals().size();
                        for (int l = 0; l < t_size; l ++) 
                            if (ret[i + 1][l] == "") ret[i + 1][l] = "r" + Utils::toString(k);
                    }
                }
            }
        }
        if (found > 1) fprintf(stderr, "WARNING: wrong grammar!\n");
    }
    return ret;
}

vector <int> LRAnalytics::parse(string str, bool quiet) const{
    str += INPUT_END_LETTER;
    string terminals = getTerminals();
    string nonTerminals = getNonTerminals();
    vector <int> ret;
    stack <int> sStates;
    map <char, int> translation;
    vector <vector <string> > table = genTable();
    for (int i = 0; i < table[0].size(); i ++) translation[table[0][i][0]] = i;
    int strPos = 0;
    sStates.push(0);
    while (1){
        int curState = sStates.top();
        const vector <string> &row = table[curState + 1];
        int curId = translation[str[strPos]];
        if (row[curId] == "acc"){
            if (!quiet) printf("Accept\n");
            break;
        }  else if (row[curId].size() > 0 && row[curId][0] == 'r'){
            int m = Utils::toInt(row[curId].substr(1));
            ret.push_back(m);
            for (int i = 0; i < _rules[m].right_side.size(); i ++) sStates.pop();
            char nt = _rules[m].left_side;
            curState = sStates.top();
            const vector <string> &newRow = table[curState + 1];
            curId = translation[nt];
            sStates.push(Utils::toInt(newRow[curId].substr(1)));
            if (!quiet) printf("Reduct %d\n", m);
        }  else if (row[curId].size() > 0 && row[curId][0] == 's'){
            int m = Utils::toInt(row[curId].substr(1));
            sStates.push(m);
            strPos ++;
            if (!quiet) printf("Shift %d\n", m);
        }  else {
            throw Exception("ERROR: unrecognizable input!\n");
        }
    }
    return ret; 
}
