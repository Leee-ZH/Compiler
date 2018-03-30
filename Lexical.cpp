//
//  Lexical.cpp
//  Compiler
//
//  Created by Wave on 2018/3/23.
//  Copyright © 2018年 Wave. All rights reserved.
//

#include "Lexical.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <map>
#include <cstdlib>
#include <cmath>

#define RESERVED_LEN 32

#define     ID              0
#define     INT             1
#define     FLOAT           2
#define     STR             3
#define     RES             4
#define     ERROR           7

#define     ELLIPSIS        10      //      ...
#define     RIGHT_ASSIGN    11      //      >>=
#define     LEFT_ASSIGN     12      //      <<=
#define     ADD_ASSIGN      13      //      +=
#define     SUB_ASSIGN      14      //      -=
#define     MUL_ASSIGN      15      //      *=
#define     DIV_ASSIGN      16      //      /=
#define     MOD_ASSIGN      17      //      %=
#define     AND_ASSIGN      18      //      &=
#define     XOR_ASSIGN      19      //      ^=
#define     OR_ASSIGN       20      //      |=
#define     RIGHT_OP        21      //      >>
#define     LEFT_OP         22      //      <<
#define     INC_OP          23      //      ++
#define     DEC_OP          24      //      --
#define     PTR_OP          25      //      ->
#define     AND_OP          26      //      &&
#define     OR_OP           27      //      ||
#define     LE_OP           28      //      <=
#define     GE_OP           29      //      >=
#define     EQ_OP           30      //      ==
#define     NE_OP           31      //      !=
#define     SEMI            32      //      ;
#define     LEFT_BRACE      33      //      {
#define     RIGHT_BRACE     34      //      }
#define     COMMA           35      //      ,
#define     COLON           36      //      :
#define     EQUAL           37      //      =
#define     LEFT_PAR        38      //      (
#define     RIGHT_PAR       39      //      )
#define     LEFT_SQUARE     40      //      [
#define     RIGHT_SQUARE    41      //      ]
#define     PERIOD          42      //      .
#define     AND             43      //      &
#define     EXCLAMATION     44      //      !
#define     BNOT            45      //      ~
#define     SUB             46      //      -
#define     ADD             47      //      +
#define     MUL             48      //      *
#define     DIV             49      //      /
#define     MOD             50      //      %
#define     LES             51      //      <
#define     GRE             52      //      >
#define     XOR             53      //      ^
#define     OR              54      //      |
#define     QUES            55      //      ?

using namespace std;

class tokenOut
{
public:
    int cate;
    int valInt;
    double valFloat;
    string valString;
};

map<string, int> OP_MAP= {{"...", ELLIPSIS}, {">>=", RIGHT_ASSIGN}, {"<<=", LEFT_ASSIGN}, {"+=", RIGHT_ASSIGN}, {"-=", LEFT_ASSIGN},
    {"*=", MUL_ASSIGN}, {"/=", DIV_ASSIGN}, {"%=", MOD_ASSIGN}, {"&=", AND_ASSIGN}, {"^=", XOR_ASSIGN}, {"|=", OR_ASSIGN}, {">>", RIGHT_OP},
    {"<<", LEFT_OP}, {"++", INC_OP}, {"--", DEC_OP}, {"->", PTR_OP}, {"&&", AND_OP}, {"||", OR_OP}, {"<=", LE_OP}, {">=", GE_OP}, {"==", EQ_OP},
    {"!=", NE_OP}, {";", SEMI}, {"{", LEFT_BRACE}, {"}", RIGHT_BRACE}, {",", COMMA}, {":", COLON}, {"=", EQUAL}, {"(", LEFT_PAR}, {")", RIGHT_PAR},
    {"[", LEFT_SQUARE}, {"]", RIGHT_SQUARE}, {".", PERIOD}, {"&", AND}, {"!", EXCLAMATION}, {"~", BNOT}, {"-", SUB}, {"+", ADD}, {"*", MUL},
    {"/", DIV}, {"%", MOD}, {"<", LES}, {">", GRE}, {"^", XOR}, {"|", OR}, {"?", QUES}
};

const string ReservedWord[] = {"auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "foto", "if", "int", "long",
    "redister", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "nuion", "unsigned", "void", "volatile", "while"
};

enum {enum0, enum1, enum2, enum3, enum4, DELI, OP};

string outPut[] = {"ID", "INT", "FLOAT", "STR", "RES", "DELI", "OP", "ERROR"};

vector<string> IDList;

string pretreat(string s)
{
    int len = (int)s.length();
    vector<char> tmp;
    for (int i = 0; i < len; i++)
    {
        if (i <= len - 3 and s.substr(i, 2) == "//")
        {
            while (i <= len - 3 and s.substr(i, 1) != "\n")
                i++;
            continue;
        }
        if (s[i] == '\n' or s[i] == '\t')
            continue;
        if (tmp.empty() and s[i] != ' ')
        {
            tmp.push_back(s[i]);
        }
        else if (!tmp.empty() and tmp.back() == ' ' and (s[i] == ' ' or s[i] == '\n' or s[i] == '\t'))
            continue;
        else
        {
            tmp.push_back(s[i]);
        }
    }
    string re = "";
    for (int i = 0; i < tmp.size(); i++)
        re += tmp[i];
    return re;
}

void formatPrint(string token, int start, int end)
{
    int tmp = Analysis(token);
    if (tmp == OP)
        cout << setw(10) << outPut[tmp] << setw(10) << judgeOp(split(token)) << setw(30) << token << endl;
    else if (tmp != ID)
        cout << setw(10) << outPut[tmp] << setw(10) << " " << setw(30) << token << endl;
    else
    {
        int IDsize = (int) IDList.size();
        for (int i = 0; i < IDsize; i++)
        {
            if (token == IDList[i])
            {
                cout << setw(10) << outPut[ID] << setw(10) << i << setw(30) << token << endl;
                return ;
            }
        }
        cout << setw(10) << outPut[ID] << setw(10) << IDsize << setw(30) << token << endl;
        IDList.push_back(token);
    }
}

void printTokenVector(vector<tokenOut>* tokens)
{
    int len = int((*tokens).size());
    cout << len << endl;
    for (int i = 0; i < len; i++)
    {
        if ((*tokens)[i].cate == 0)
            cout << setw(10) << (*tokens)[i].cate << "\t\t" << setw(20) << (*tokens)[i].valInt << endl;
        else if ((*tokens)[i].cate == 1)
            cout << setw(10) << (*tokens)[i].cate << "\t\t" << setw(20) << (*tokens)[i].valInt << endl;
        else if ((*tokens)[i].cate == 2)
            cout << setw(10) << (*tokens)[i].cate << "\t\t" << setw(20) << (*tokens)[i].valFloat << endl;
        else if ((*tokens)[i].cate == 3)
            cout << setw(10) << (*tokens)[i].cate << "\t\t" << setw(20) << (*tokens)[i].valString << endl;
        else
            cout << setw(10) << (*tokens)[i].cate << "\t\t" << endl;
        
    }
}

void addToken(vector<tokenOut>* result, string token, int Type = -1)
{
    tokenOut tmp;
    tmp.cate = Type;
    if (Type == STR)
        tmp.valString = token;
    else if (Type == -1)
        tmp.cate = judgeOp(split(token));
    else if (Type == ID)
    {
        int flag = 0;
        for (int i = 0; i < int(IDList.size()); i++)
        {
            if (IDList[i] == token)
            {
                tmp.valInt = i;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            tmp.valInt = int(IDList.size());
            IDList.push_back(token);
        }
    }
    else if (tmp.cate == INT)
        tmp.valInt = atoi(token.c_str());
    else if (tmp.cate == FLOAT)
        tmp.valFloat = atof(token.c_str());
    (*result).push_back(tmp);
}

vector<string> split(string a)
{
    vector<string> re;
    int len = (int)a.length();
    for (int i = 0; i < len; i++)
        re.push_back(a.substr(i, 1));
    return re;
}

bool judgeID(vector<string> splitToken)
{
    int tokenLen = int (splitToken.size());
    char tmp0 = splitToken[0][0];
    if (!isalpha(tmp0))
        return false;
    else
    {
        for (int i = 1; i < tokenLen; i++)
        {
            tmp0 = splitToken[i][0];
            if (not (isalnum(tmp0) or tmp0 == '_'))
                return false;
        }
    }
    return true;
}

int judgeInt(vector<string> splitToken)
{
    splitToken.push_back(" ");
    int tokenLen = int (splitToken.size());
    if (tokenLen == 1)
        return -1;
    char tmp0 = splitToken[0][0];
    if (tmp0 == '0')
    {
        if (tokenLen == 2)
        {
            if (splitToken[1][0] < '0' or splitToken[1][0] > '9')
                return 1;
            // Return DEC
        }
        // Return int zero;
        else if (tokenLen > 2)
        {
            if (splitToken[1][0] == 'x' and tokenLen > 3)
            {
                for (int i = 2; i < tokenLen - 1; i++)
                    if (not ((splitToken[i][0] >= '0' and splitToken[i][0] <= '9') or ((splitToken[i][0] >= 'a' and splitToken[i][0] <= 'e'))))
                        return -1;
                if ((splitToken[tokenLen - 1][0] >= '0' and splitToken[tokenLen - 1][0] <= '9') or ((splitToken[tokenLen - 1][0] >= 'a' and
                                                                                                     splitToken[tokenLen - 1][0] <= 'e')))
                    return -1;
                return 2;
                // Return HEX
            }
            if (splitToken[1][0] != 'x')
            {
                for (int i = 1; i < tokenLen - 1; i++)
                    if (not (splitToken[i][0] >= '0' and splitToken[i][0] <= '8'))
                        return -1;
                if (splitToken[tokenLen - 1][0] >= '0' and splitToken[tokenLen - 1][0] <= '8')
                    return -1;
                return 3;
                //return OCT
            }
        }
    }
    else
    {
        for (int i = 0; i < tokenLen - 1; i++)
            if (not (splitToken[i][0] >= '0' and splitToken[i][0] <= '9'))
                return -1;
        if (splitToken[tokenLen - 1][0] >= '0' and splitToken[tokenLen - 1][0] <= '9')
            return -1;
        return 1;
        // Return DEC
    }
    return -1;
}

int judgeFloat(vector<string> splitToken)
{
    int tokenLen = int (splitToken.size()), point = 0;
    char tmp0;
    if (tokenLen == 0 or tokenLen == 1)
        return 0;
    for (int i = 0; i < tokenLen; i++)
    {
        tmp0 = splitToken[i][0];
        if (tmp0 == '.' or (tmp0 >= '0' and tmp0 <= '9'))
        {
            if (tmp0 == '.' and point == 0)
                point ++;
            else if (tmp0 == '.' and point != 0)
                return 0;
        }
        else
            return 0;
    }
    if (point == 1)
        return 1;
    else
        return 0;
}

int judgeStr(vector<string> splitToken)
{
    int tokenLen = int (splitToken.size());
    if (splitToken[0][0] == '"')
        return 1;
    if (tokenLen > 2 and splitToken[0][0] == '\"' and splitToken[tokenLen - 2][0] == '\"')
        return 1;
    return 0;
}

bool judgeRes(vector<string> splitToken)
{
    int tokenLen = int (splitToken.size()), flag = 0;
    string pre = "";
    for (int i = 0; i < tokenLen - 1; i++)
        pre += splitToken[i];
    for (int i = 0; i < RESERVED_LEN; i++)
        if (pre == ReservedWord[i])
            flag = 1;
    if (flag == 1 and (not isalnum(splitToken[tokenLen - 1][0])))
        return 1;
    return 0;
}

int judgeOp(vector<string> splitToken)
{
    int tokenLen = int (splitToken.size());
    string pre = "";
    for (int i = 0; i < tokenLen; i++)
        pre += splitToken[i];
    if (tokenLen == 1 or tokenLen == 2 or tokenLen == 3)
        for (map<string, int>::iterator strint = OP_MAP.begin(); strint != OP_MAP.end(); strint++)
            if (strint->first == pre)
                return strint->second;
    return -1;
}

int Analysis(string token)
{
    for (int i = 0; i < RESERVED_LEN; i++)
        if (token == ReservedWord[i])
            return RES;
    // Check whether the token is a reserved word;
    
    int tokenLen = int (token.length());
    vector<string> splitToken;
    for (int i = 0; i < tokenLen; i++)
        splitToken.push_back(token.substr(i, 1));
    
    if (judgeOp(splitToken) != -1)
        return OP;
    // 6 OP detected, fallback until 8 returned;
    
    if (judgeRes(splitToken))
        return RES;
    // 4 RES, fallback;
    
    if (judgeFloat(splitToken))
        return FLOAT;
    // 2 FLOAT, fallback.
    
    int intType = judgeInt(splitToken);
    if (intType != -1)
        return INT;
    // 1 INT, fallback.
    
    if (judgeID(splitToken))
        return ID;
    // 0 ID, fallback.
    
    if (judgeStr(splitToken))
        return STR;
    // 3 STR, fallback.
    
    return ERROR;
    // 7 Error
}

vector<tokenOut>* Lexical(string file)
{
    static vector<tokenOut> result;
    ifstream fp(file);
    string s = "", tmp, token;
    while(getline(fp, tmp))
        s += tmp + "\n";
    s = pretreat(s);
    int start = 0, end = 0, len = int(s.length()), strflag;
    cout << "Length of the code:\t" << len << endl << endl;
    
    int startIsAlnum, endIsAlnum;
    
    while (start <= len and end <= len)
    {
        if (s.substr(start, 1) == " ")
        {
            start ++;
            end ++;
            continue;
        }
        // Skip " "
        
        if (start == end or s.substr(end, 1) == "_")
            end ++;
        
        if (s.substr(start, 1) == "\"")
        {
            strflag = 1;
            while (s.substr(end, 1) != "\"")
                end ++;
            token = s.substr(start, end - start + 1);
            addToken(&result, token, STR);
            // formatPrint(token, start, end - 1);
            end++;
            start = end;
        }
        // Handle with strings
        
        if (s.substr(end, 1) == ".")
            if( !isalpha(s.substr(end - 1, 1)[0]) and !isalpha(s.substr(end + 1, 1)[0]))
                end ++;
        // Handle with floats
        
        startIsAlnum = isalnum(s.substr(start, 1)[0]);
        endIsAlnum = isalnum(s.substr(end, 1)[0]);
        if (startIsAlnum == endIsAlnum)
        {
            if (startIsAlnum == 0)
            {
                int subAna1 = Analysis(s.substr(start, 1)), subAna2 = Analysis(s.substr(start, 2));
                if (subAna1 == OP and subAna2 == OP)
                {
                    int subAna3 = Analysis(s.substr(start, 3));
                    if (subAna3 == OP)
                    {
                        token = s.substr(start, 3);
                        addToken(&result, token);
                        // formatPrint(token, start, start + 4);
                        start += 3;
                        end = start;
                        continue;
                    }
                    // Len of the OP == 3
                    else
                    {
                        token = s.substr(start, 2);
                        addToken(&result, token);
                        // formatPrint(token, start, start + 3);
                        start += 2;
                        end = start;
                        continue;
                    }
                    // Len of the OP == 2
                }
                // Len of the OP may be more than 2
                else
                {
                    token = s.substr(start, 1);
                    addToken(&result, token);
                    // formatPrint(token, start, end);
                    start += 1;
                    end = start;
                    continue;
                }
                // Len of the OP == 1
            }
            end ++;
            continue;
        }
        else
        {
            string token = s.substr(start, end - start);
            tokenOut tmp;
            tmp.cate = Analysis(token);
            addToken(&result, token, tmp.cate);
            // formatPrint(token, start, end);
            start = end;
            end ++;
        }
    }
    return &result;
}
