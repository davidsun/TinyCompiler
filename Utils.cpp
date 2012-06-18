#include <stdio.h>

#include "Utils.h"

int Utils::toInt(const string &s){
    int ret;
    sscanf(s.c_str(), "%d", &ret);
    return ret;
}

string Utils::toString(int x){
    char s[20];
    sprintf(s, "%d", x);
    return s;
}

string Utils::toString(double x){
    char s[20];
    sprintf(s, "%e", x);
    return s;
}
