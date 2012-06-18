#ifndef _ITEMCODE_H
#define _ITEMCODE_H

#include <string>
#include <vector>

using namespace std;

class CodeItem{
    public:
        CodeItem(const string &command, char param1, char param2);
        CodeItem(const CodeItem &code_item);

        CodeItem &operator = (const CodeItem &code_item);
        bool operator == (const CodeItem &code_item) const;
        
        string command;
        char param1;
        char param2;
};

typedef vector <CodeItem> ListCodeItems;

#endif
