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
