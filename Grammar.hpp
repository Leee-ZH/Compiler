//
//  Grammar.hpp
//  Compiler
//
//  Created by Wave on 2018/4/4.
//  Copyright © 2018年 Wave. All rights reserved.
//

#ifndef Grammar_hpp
#define Grammar_hpp

#include <string>
#include "Syntax.hpp"

using namespace std;

class tokenOut;

vector<vector<string>> readProd(string path);
vector<vector<string>> readTable(string path);
vector<string> Grammar(vector<tokenOut>* tokens, vector<vector<string>> table, vector<vector<string>> prod);
nameTable returnGlobalNameTable();

#endif /* Grammar_hpp */
