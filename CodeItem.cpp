#include <stdio.h>

#include "CodeItem.h"

CodeItem::CodeItem(const string &command, char param1, char param2) : command(command), param1(param1), param2(param2){
}

CodeItem::CodeItem(const CodeItem &code_item) : command(code_item.command), param1(code_item.param1), param2(code_item.param2){
}

CodeItem &CodeItem::operator = (const CodeItem &code_item){
    command = code_item.command;
    param1 = code_item.param1;
    param2 = code_item.param2;
    return *this;
}

bool CodeItem::operator == (const CodeItem &code_item) const{
    return (command == code_item.command && param1 == code_item.param1 && param2 == code_item.param2);
}

