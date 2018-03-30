//
//  main.cpp
//  Compile
//
//  Created by Wave on 2018/3/23.
//  Copyright © 2018年 Wave. All rights reserved.
//

#include "LexicalAnalysis.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

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
    vector<tokenOut>* tokens = Lexical("/Users/wave/Desktop/Compile/code.txt");
    printTokenVector(tokens);
    return 0;
}


