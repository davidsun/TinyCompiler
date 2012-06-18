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
