//
//  Syntax.hpp
//  Compiler
//
//  Created by Wave on 2018/5/10.
//  Copyright © 2018年 Wave. All rights reserved.
//

#ifndef Syntax_hpp
#define Syntax_hpp

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

struct nameTable
{
    struct nameTableElement
    {
        std::string funVarName;
        std::string type;
        int offsetList;
        nameTable *childTable;
    };
    
    nameTable* parentTable;
    std::string parentName;
    int inmedVariableNo = -1;
    std::vector<nameTableElement> content;
    
    unsigned long getSize()
    {
        return content.size();
    }
    
    void push_back(std::string funVarName, std::string type, int offset, nameTable* childTable)
    {
        content.push_back({funVarName, type, offset, childTable});
    }
    
    void set_parent_table(nameTable* parentTable)
    {
        this->parentTable = parentTable;
    }
    
    void set_parent_name(std::string parentName)
    {
        this->parentName = parentName;
    }
    
    void pop_back()
    {
        content.pop_back();
    }
    
    nameTableElement operator[](int i)
    {
        return content[i];
    }
};

struct triAdd
{
    string op;
    string fri;
    string sec;
    string thr;
};
triAdd getTriAdd(int a, int b, vector<string> popedToekn, nameTable* globalTable);

#endif /* Syntax_hpp */
