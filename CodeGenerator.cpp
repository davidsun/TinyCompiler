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

#include <algorithm>

#include "CodeGenerator.h"
#include "Utils.h"

vector <string> CodeGenerator::parse(const LRAnalytics &lr_analytics, const vector <pair <char, string> > &la_result, const vector <int> &lra_result, const vector <ListCodeItems> &code_rules){
    _lra_position = lra_result.size() - 1;
    _la_position = la_result.size() - 1;
    _tmp_count = 0;
    _label_count = 0;
    _lr_analytics = lr_analytics;
    _la_result = la_result;
    _lra_result = lra_result;
    _code_rules = code_rules;
    return parse_p().second;
}

pair <string, vector <string> > CodeGenerator::parse_p(){
    int current_rule = _lra_result[_lra_position];
    _lra_position --;
    const string &rule = _lr_analytics.getRules()[current_rule].right_side;
    vector <string> apps;
    vector <vector <string> > parses;
    for (int i = rule.size() - 1; i >= 0; i --){
        if (rule[i] == _la_result[_la_position].first){
            if (rule[i] <= 'Z' && rule[i] >= 'A'){
                apps.push_back(string() + rule[i] + _la_result[_la_position].second);
                parses.push_back(vector <string>());
            }
            _la_position --;
        }  else {
            pair <string, vector <string> > result = parse_p();
            apps.push_back(string(" ") + result.first);
            parses.push_back(result.second);
        }
    }
    reverse(apps.begin(), apps.end());
    reverse(parses.begin(), parses.end());
    const ListCodeItems &lst_code_items = _code_rules[current_rule];
    _tmp_count ++;
    string ret_var_name = "t." + Utils::toString(_tmp_count);
    vector <string> codes;
    int label_start = _label_count;
    for (int i = 0; i < lst_code_items.size(); i ++){
        const string &command = lst_code_items[i].command;
        if (command == "PARSE"){
            // Parse command
            int pos = lst_code_items[i].param1 - '0';
            codes.insert(codes.end(), parses[pos].begin(), parses[pos].end());
        }  else if (command == "LABEL"){
            // Label
            if (lst_code_items[i].param1 == '-'){
                _label_count ++;
                string lbl_name = "L." + Utils::toString(_label_count);
                codes.push_back(lbl_name + ":");
            }  else {
                codes.push_back("L." + apps[lst_code_items[i].param1 - '0'].substr(1) + ":");
            }
        }  else if (command == "J"){
            // Jump
            codes.push_back(lst_code_items[i].command + "\tL." + Utils::toString(label_start + 1 + lst_code_items[i].param1 - '0')); 
        }  else if (command == "CALL"){
            // Call
            string as = lst_code_items[i].command + "\tL." + apps[lst_code_items[i].param1 - '0'].substr(1);
            if (lst_code_items[i].param2 == 'N'){
                as += string("\t") + ret_var_name;
            }  else if (lst_code_items[i].param2 != '-'){
                as += string("\t") + apps[lst_code_items[i].param2 - '0'].substr(1);
            }
            codes.push_back(as);
        }  else if (command == "BEQZ" || command == "BGEZ" || command == "BGTZ" || command == "BLEZ" || command == "BLTZ"){
            // Conditional Jump
            string as = lst_code_items[i].command + '\t';
            if (lst_code_items[i].param1 == 'N'){
                as += ret_var_name;
            }  else if (lst_code_items[i].param1 != '-'){
                as += apps[lst_code_items[i].param1 - '0'].substr(1);
            }
            as += "\tL." + Utils::toString(label_start + 1 + lst_code_items[i].param2 - '0');
            codes.push_back(as);
        }  else {
            string as = lst_code_items[i].command;
            if (lst_code_items[i].param1 == 'N'){
                as += string("\t") + ret_var_name;
            }  else if (lst_code_items[i].param1 != '-'){
                as += string("\t") + apps[lst_code_items[i].param1 - '0'].substr(1);
            }
            if (lst_code_items[i].param2 == 'N'){
                as += string("\t") + ret_var_name;
            }  else if (lst_code_items[i].param2 == 'T'){
                as += string("\t") + "1";
            }  else if (lst_code_items[i].param2 == 'F'){
                as += string("\t") + "0";
            }  else if (lst_code_items[i].param2 != '-'){
                as += string("\t") + apps[lst_code_items[i].param2 - '0'].substr(1);
            }
            codes.push_back(as);
        }
    }
    return make_pair(ret_var_name, codes);
}


