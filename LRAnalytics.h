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
