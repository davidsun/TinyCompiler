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

#ifndef _LEXICALANALYTICS_H
#define _LEXICALANALYTICS_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class LexicalAnalytics{
    public:
        const static int TYPE_TOKEN;
        const static int TYPE_BLANK;
        const static int TYPE_NORMAL;

        LexicalAnalytics();
        vector <pair <char, string> > parse(string input) const;

    private:
        int getType_p(char c) const;
};

#endif
