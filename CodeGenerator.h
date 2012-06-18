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

#ifndef _CODEGENERATOR
#define _CODEGENERATOR

#include <map>
#include <vector>
#include <string>

#include "CodeItem.h"
#include "LRAnalytics.h"

using namespace std;

class CodeGenerator{
    public:
        vector <string> parse(const LRAnalytics &lr_analytics, const vector <pair <char, string> > &la_result, const vector <int> &lra_result, const vector <ListCodeItems> &code_rules);

    private:
        int _lra_position;
        int _la_position;
        int _tmp_count;
        int _label_count;
        LRAnalytics _lr_analytics;
        vector <pair <char, string> > _la_result;
        vector <int> _lra_result;
        vector <ListCodeItems> _code_rules;

        pair <string, vector <string> > parse_p();
};

#endif
