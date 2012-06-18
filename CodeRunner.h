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

#ifndef _CODERUNNER_H
#define _CODERUNNER_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class Variable{
    public:
        Variable();
        Variable(const string &type, const string &value);
        Variable(const Variable &variable);

        Variable &operator = (const Variable &variable);

        string type;
        string value;
};

class CodeRunner{
    public:
        void execute(const vector <string> &codes);

    private:
        Variable *getVariable_p(const map <int, map <string, Variable *> > &variables, const vector <int> &scopes_count, const string &name);
};

#endif
