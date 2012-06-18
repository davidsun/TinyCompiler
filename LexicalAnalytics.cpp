#include <stdio.h>

#include "LexicalAnalytics.h"
#include "Exception.h"

const int LexicalAnalytics::TYPE_NORMAL = 0;
const int LexicalAnalytics::TYPE_TOKEN = 1;
const int LexicalAnalytics::TYPE_BLANK = 2;

LexicalAnalytics::LexicalAnalytics(){
}

vector <pair <char, string> > LexicalAnalytics::parse(string input) const{
    int last_type = -1;
    string last_token = "";
    vector <pair <char, string> > ret;
    input += " ";
    for (int i = 0; i < input.size(); i ++){
        int cur_type = getType_p(input[i]);
        if (cur_type != last_type){
            if (last_token.length() > 0 && last_type != TYPE_BLANK){
                if (last_type == TYPE_TOKEN){
                    for (int j = 0; j < last_token.length(); j ++){
                        ret.push_back(make_pair(last_token[j], string() + last_token[j]));
                    }
                }  else if (last_token == "int" || last_token == "double"){
                    ret.push_back(make_pair('T', last_token));
                }  else if (last_token == "if"){
                    ret.push_back(make_pair('W', last_token));
                }  else if (last_token == "else"){
                    ret.push_back(make_pair('U', last_token));
                }  else if (last_token == "while"){
                    ret.push_back(make_pair('L', last_token));
                }  else if (last_token == "return"){
                    ret.push_back(make_pair('G', last_token));
                }  else if (last_token[0] <= '9' && last_token[0] >= '0'){
                    int point_count = 0;
                    for (int j = 0; j < last_token.length(); j ++){
                        if (last_token[j] <= '9' && last_token[j] >= '0'){
                        }  else if (last_token[j] == '.'){
                            point_count ++;
                        }  else {
                            throw Exception("Lexical analytics: error on token " + last_token + ".");
                        }
                    }
                    if (point_count > 1){
                        throw Exception("Lexical analytics: error on token " + last_token + ".");
                    }
                    ret.push_back(make_pair((point_count > 0) ? 'J' : 'I', last_token));
                }  else {
                    ret.push_back(make_pair('N', last_token));
                }
            }
            last_token = input[i];
            last_type = cur_type; 
        }  else {
            last_token += input[i];
        }
    }
    return ret;
}

int LexicalAnalytics::getType_p(char c) const{
    switch (c){
        case ';':
        case ':':
        case '(':
        case ')':
        case '{':
        case '}':
        case '*':
        case '/':
        case '+':
        case '-':
        case '=':
        case '<':
        case '>':
        case ',':
        case '!':
        case '?':
            return TYPE_TOKEN;
        case '\t':
        case '\n':
        case '\r':
        case ' ':
            return TYPE_BLANK;
    }
    return TYPE_NORMAL;
}
