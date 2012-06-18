#include <stdio.h>

#include <stack>
#include <vector>
#include <map>

#include "LexicalAnalytics.h"
#include "LRAnalytics.h"
#include "Utils.h"
#include "CodeItem.h"
#include "CodeGenerator.h"
#include "CodeRunner.h"

int main(void){
    LexicalAnalytics la;
    FILE *fprog = fopen("program.txt", "r");
    string program;
    int ch;
    while ((ch = fgetc(fprog)) != EOF){
        program += (char)ch;
    }
    vector <pair <char, string> > la_result = la.parse(program);
    string la_result_str;
    for (int i = 0; i < la_result.size(); i ++) la_result_str += la_result[i].first;

    LRAnalytics lra;
    FILE *f = fopen("input.txt", "r");
    vector <ItemSet> sets = lra.genStates();
    vector <ListCodeItems> code_items;
    ListCodeItems code_items_tmp;
    char s[100];
    while (fgets(s, 100, f)){
        if (s[0] == '#'){
            char s1[100], s2[100];
            sscanf(s + 1, "%s%s", s1, s2);
            string ss2 = s2;
            if (ss2 == "<EMPTY>") ss2 = "";
            lra.addRule(s1[0], ss2);
            code_items.push_back(code_items_tmp);
            code_items_tmp.clear();
        }  else {
            char s1[100], s2[100], s3[100];
            if (sscanf(s, "%s%s%s", s1, s2, s3) == 3) code_items_tmp.push_back(CodeItem(s1, s2[0], s3[0]));
        }
    }
    code_items.push_back(code_items_tmp);
    fclose(f);

    vector <int> lra_result = lra.parse(la_result_str, true);
    for (int i = 0; i < lra_result.size(); i ++){
        printf("%d\n", lra_result[i]);
    }
    CodeGenerator g;
    vector <string> ret = g.parse(lra, la_result, lra_result, code_items);
    for (int i = 0; i < ret.size(); i ++){
        printf("%d: %s\n", i + 1, ret[i].c_str());
    }

    CodeRunner r;
    r.execute(ret);
    return 0;
}
