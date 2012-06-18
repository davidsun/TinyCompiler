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
