//
//  Syntax.cpp
//  Compiler
//
//  Created by Wave on 2018/5/10.
//  Copyright © 2018年 Wave. All rights reserved.
//

#include "Syntax.hpp"
#include <string>
#include <vector>

using namespace std;

int getOffset(string s)
{
    int re = -1;
    if (s == "INT")
        re = 4;
    return re;
}

triAdd getTriAdd(int a, int b, vector<string> popedToekn, nameTable* globalTable)
{
    triAdd re;
    //  declaration    ->    declaration_specifiers    init_declarator_list    ;
    if (a == 88)
    {
        if (b == 2)
        {
            (*globalTable).push_back(popedToekn[1], popedToekn[0], getOffset(popedToekn[1]), NULL);
        }
    }
    return re;
}
