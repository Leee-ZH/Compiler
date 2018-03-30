//
//  Lexical.hpp
//  Compiler
//
//  Created by Wave on 2018/3/23.
//  Copyright © 2018年 Wave. All rights reserved.
//

#ifndef Lexical_hpp
#define Lexical_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class tokenOut;
int judgeOp(vector<string> splitToken);
int Analysis(std::string token);
void formatPrint(string token, int start, int end);
void printTokenVector(vector<tokenOut>* tokens);
string pretreat(string s);
vector<string> split(string a);
vector<tokenOut>* Lexical(string file);


#endif /* Lexical_hpp */



