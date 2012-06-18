#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "CodeRunner.h"
#include "Exception.h"
#include "Utils.h"

Variable::Variable(){
}

Variable::Variable(const string &type, const string &value) : type(type), value(value){
}

Variable::Variable(const Variable &variable) : type(variable.type), value(variable.value){
}

Variable &Variable::operator = (const Variable &variable){
    type = variable.type;
    value = variable.value;
    return *this;
}

void CodeRunner::execute(const vector <string> &codes){
    map <int, map <string, Variable *> > variables;
    map <string, int> labels;
    vector <pair <int, string> > call_stack;
    vector <vector <int> > scopes_stack;
    vector <Variable> variable_stack;
    int scopes_count = 0;
    for (int i = 0; i < codes.size(); i ++)
        if (codes[i].length() > 0 && codes[i][codes[i].length() - 1])
            labels[codes[i].substr(0, codes[i].length() - 1)] = i;
    if (labels.find("L.main") == labels.end()) throw Exception("ERROR: Cannot find the entry of the code.");
    call_stack.push_back(make_pair(-1, "#"));
    scopes_stack.push_back(vector <int>());
    for (int location = labels["L.main"]; ; location ++){
        const string &cmd = codes[location];
        vector <int> &cur_scopes = scopes_stack[scopes_stack.size() - 1];
        if (cur_scopes.size() == 0) cur_scopes.push_back(++ scopes_count);
        int cur_scope = cur_scopes[cur_scopes.size() - 1];
        if (cmd == "SCOPE"){
            scopes_count ++;
            cur_scopes.push_back(scopes_count);
        }  else if (cmd == "ENDSCOPE"){
            cur_scopes.pop_back();
            if (variables.find(cur_scope) != variables.end())
                for (map <string, Variable *>::iterator it = variables[cur_scope].begin(); it != variables[cur_scope].end(); it ++) delete it -> second;
        }  else if (cmd.substr(0, 7) == "ASSIGN\t"){
            char s1[100], s2[100];
            sscanf(cmd.c_str(), "%*s%s%s", s1, s2);
            string a = s1, b = s2;
            if (b == "int" || b == "double"){
                if (getVariable_p(variables, cur_scopes, a))
                    throw Exception("ERROR: Duplicate variable allocation " + a + " on line " + Utils::toString(location + 1) + ".");
                variables[cur_scope][a] = new Variable(b, "0");
            }  else if (b[0] <= '9' && b[0] >= '0'){
                Variable *va = getVariable_p(variables, cur_scopes, a);
                if (!va) variables[cur_scope][a] = new Variable(b.find('.') != string::npos ? "double" : "int", b);
                else {
                    if (va -> type == "int") va -> value = Utils::toString(atoi(b.c_str()));
                    else va -> value = Utils::toString(atof(b.c_str()));
                }
            }  else {
                Variable *va = getVariable_p(variables, cur_scopes, a);
                Variable *vb = getVariable_p(variables, cur_scopes, b);
                if (!vb) throw Exception("ERROR: Unknown variable " + b + " on line " + Utils::toString(location + 1) + ".");
                if (!va){
                    if (a.substr(0, 2) != "t.") throw Exception("ERROR: Unknown variable " + a + " on line " + Utils::toString(location + 1) + ".");
                    else variables[cur_scope][a] = new Variable(*vb);
                }  else {
                    if (va -> type == "int") va -> value = Utils::toString(atoi(vb -> value.c_str()));
                    else va -> value = Utils::toString(atof(vb -> value.c_str()));
                }
            }
        }  else if (cmd.substr(0, 4) == "ADD\t" || cmd.substr(0, 4) == "SUB\t" || cmd.substr(0, 4) == "MUL\t" || cmd.substr(0, 4) == "DIV\t"){
            char s1[100], s2[100];
            sscanf(cmd.c_str(), "%*s%s%s", s1, s2);
            string a = s1, b = s2;
            Variable *va = getVariable_p(variables, cur_scopes, a);
            Variable *vb = getVariable_p(variables, cur_scopes, b);
            if (!va) throw Exception("ERROR: Unknown variable " + a + " on line " + Utils::toString(location + 1) + ".");
            if (!vb) throw Exception("ERROR: Unknown variable " + b + " on line " + Utils::toString(location + 1) + ".");
            if (va -> type == "double" || vb -> type == "double"){
                double a = atof(va -> value.c_str());
                double b = atof(vb -> value.c_str());
                double result = a;
                string sc = cmd.substr(0, 4);
                if (sc == "ADD\t") result += b;
                else if (sc == "SUB\t") result -= b;
                else if (sc == "MUL\t") result *= b;
                else if (sc == "DIV\t") result /= b;
                if (va -> type == "int") va -> value = Utils::toString((int)result);
                else va -> value = Utils::toString(result);
            }  else {
                int a = atoi(va -> value.c_str());
                int b = atoi(vb -> value.c_str());
                string sc = cmd.substr(0, 4);
                if (sc == "ADD\t") va -> value = Utils::toString(a + b);
                else if (sc == "SUB\t") va -> value = Utils::toString(a - b);
                else if (sc == "MUL\t") va -> value = Utils::toString(a * b);
                else if (sc == "DIV\t") va -> value = Utils::toString(a / b);
            }
        }  else if (cmd.substr(0, 5) == "BEQZ\t" || cmd.substr(0, 5) == "BGEZ\t" || cmd.substr(0, 5) == "BGTZ\t" || cmd.substr(0, 5) == "BLEZ\t" || cmd.substr(0, 5) == "BLTZ\t"){
            char s1[100], s2[100];
            sscanf(cmd.c_str(), "%*s%s%s", s1, s2);
            string a = s1, b = s2;
            Variable *va = getVariable_p(variables, cur_scopes, a);
            if (!va) throw Exception("ERROR: Unknown variable " + a + " on line " + Utils::toString(location + 1) + ".");
            if (labels.find(b) == labels.end()) throw Exception("ERROR: Unknown label " + b + " on line " + Utils::toString(location + 1) + ".");
            int should_jmp = 0;
            string sc = cmd.substr(0, 5);
            if (va -> type == "double"){
                double a = atof(va -> value.c_str());
                if (sc == "BEQZ\t" && a == 0.0) should_jmp = 1;
                else if (sc == "BGEZ\t" && a >= 0.0) should_jmp = 1;
                else if (sc == "BGTZ\t" && a > 0.0) should_jmp = 1;
                else if (sc == "BLEZ\t" && a <= 0.0) should_jmp = 1;
                else if (sc == "BLTZ\t" && a < 0.0) should_jmp = 1;
            }  else {
                int a = atoi(va -> value.c_str());
                if (sc == "BEQZ\t" && a == 0.0) should_jmp = 1;
                else if (sc == "BGEZ\t" && a >= 0.0) should_jmp = 1;
                else if (sc == "BGTZ\t" && a > 0.0) should_jmp = 1;
                else if (sc == "BLEZ\t" && a <= 0.0) should_jmp = 1;
                else if (sc == "BLTZ\t" && a < 0.0) should_jmp = 1;
            }
            if (should_jmp) location = labels[b];
        }  else if (cmd.substr(0, 2) == "J\t"){
            char s1[100];
            sscanf(cmd.c_str(), "%*s%s", s1);
            if (labels.find(s1) == labels.end()) throw Exception("ERROR: Unknown label " + string(s1) + " on line " + Utils::toString(location + 1) + ".");
            location = labels[s1];
        }  else if (cmd.substr(0, 5) == "PUSH\t"){
            char s1[100];
            sscanf(cmd.c_str(), "%*s%s", s1);
            string a = s1;
            Variable *va = getVariable_p(variables, cur_scopes, a);
            if (!va) throw Exception("ERROR: Unknown variable " + a + " on line " + Utils::toString(location + 1) + ".");
            variable_stack.push_back(*va);
        }  else if (cmd.substr(0, 4) == "POP\t"){
            char s1[100];
            sscanf(cmd.c_str(), "%*s%s", s1);
            string a = s1;
            Variable *va = getVariable_p(variables, cur_scopes, a);
            if (!va) throw Exception("ERROR: Unknown variable " + a + " on line " + Utils::toString(location + 1) + ".");
            (*va) = variable_stack[variable_stack.size() - 1];
            variable_stack.pop_back();
        }  else if (cmd.substr(0, 5) == "CALL\t"){
            char s1[100], s2[100];
            sscanf(cmd.c_str(), "%*s%s%s", s1, s2);
            string a = s1, b = s2;
            Variable *vb = getVariable_p(variables, cur_scopes, b);
            if (labels.find(a) == labels.end()) throw Exception("ERROR: Unknown label " + a + " on line " + Utils::toString(location + 1) + ".");
            if (!vb) variables[cur_scope][b] = new Variable("double", "0");
            call_stack.push_back(make_pair(location, b));
            scopes_stack.push_back(vector <int>());
            location = labels[a];
        }  else if (cmd.substr(0, 4) == "RET\t"){
            char s1[100];
            sscanf(cmd.c_str(), "%*s%s", s1);
            string a = s1;
            Variable *va = getVariable_p(variables, cur_scopes, a);
            if (!va) throw Exception("ERROR: Unknown variable " + a + " on line " + Utils::toString(location + 1) + ".");
            scopes_stack.pop_back();
            if (scopes_stack.size() == 0) break;
            const vector <int> &cs = scopes_stack[scopes_stack.size() - 1];
            Variable *vret = getVariable_p(variables, cs, call_stack[call_stack.size() - 1].second);
            *vret = *va;
            location = call_stack[call_stack.size() - 1].first;
            call_stack.pop_back();
        }
        printf("After %d:", location + 1);
        for (int i = 0; i < cur_scopes.size(); i ++){
            if (variables.find(cur_scopes[i]) == variables.end()) continue;
            for (map <string, Variable *>::iterator it = variables[cur_scopes[i]].begin(); it != variables[cur_scopes[i]].end(); it ++)
                if (it -> first.substr(0, 2) != "t.") printf("\t%s:%s", it -> first.c_str(), it -> second -> value.c_str());
        }
        printf("\n");
    }
}

Variable *CodeRunner::getVariable_p(const map <int, map <string, Variable *> > &variables, const vector <int> &cur_scopes, const string &name){
    for (int i = 0; i < cur_scopes.size(); i ++){
        map <int, map <string, Variable *> >::const_iterator it = variables.find(cur_scopes[i]);
        if (it != variables.end()){
            map <string, Variable *>::const_iterator itx = it -> second.find(name);
            if (itx != it -> second.end()) return itx -> second;
        }
    }
    return 0;
}
