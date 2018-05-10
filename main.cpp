//
//  main.cpp
//  Compiler
//
//  Created by Wave on 2018/3/23.
//  Copyright © 2018年 Wave. All rights reserved.
//

#include "Lexical.hpp"
#include "Grammar.hpp"
#include <fstream>
// #include <iostream>
#include <iomanip>
// #include <vector>

using namespace std;

class tokenOut
{
public:
    int cate;
    int valInt;
    double valFloat;
    string valString;
};

int main() {
    vector<tokenOut>* tokens = Lexical("/Users/wave/Downloads/Course/Compiler_Principle/Compiler/Compiler/code.txt");
    printTokenVector(tokens);
    vector<vector<string>> prod = readProd("/Users/wave/Downloads/Course/Compiler_Principle/Compiler/Grammar/Production.txt");
    vector<vector<string>> table = readTable("/Users/wave/Downloads/Course/Compiler_Principle/Compiler/Grammar/table.txt");
    Grammar(tokens, table, prod);
    returnGlobalNameTable();
    return 0;
}
