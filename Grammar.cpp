//
//  Grammar.cpp
//  Compiler
//
//  Created by Wave on 2018/4/4.
//  Copyright © 2018年 Wave. All rights reserved.
//

#include "Grammar.hpp"
#include <vector>
#include <stack>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

vector<vector<vector<string>>> Prod;

const string ReservedWord[] = {"auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "nuion", "unsigned", "void", "volatile", "while"
};

class tokenOut
{
public:
    int cate;
    int valInt;
    double valFloat;
    string valString;
};

int findIndex(vector<string> l0, string s)
{
    for (int i = 0; i < l0.size(); i++)
        if (l0[i] == s)
            return i;
    return -1;
}

string toUpper(string s)
{
    string tmp = "";
    for (int i = 0; i < s.size(); i++)
        tmp += s[i] - 32;
    return tmp;
}

vector<int> indextTab(string s)
{
    vector<int> re;
    for (int i = 0; i < s.length(); i++)
        if (s.substr(i, 1) == "\t")
            re.push_back(i);
    while (re.back() == s.length() - 1 or re.back() == s.length() - 2)
        re.pop_back();
    return re;
}

vector<vector<string>> readProd(string path)
{
    fstream prodfile;
    prodfile.open(path, ios::in);
    string tmp;
    vector<vector<string>> prod;
    while(!prodfile.eof())
    {
        getline(prodfile, tmp);
        vector<int> index = indextTab(tmp);
        vector<string> tmpprod;
        for (int i = 0, printto = 0; i < index.size(); printto = index[i], i++)
        {
            if (i != index.size() - 1 and index[i] == 1 and index[i+1] == 1)
            {
                i++;
                printto++;
                continue;
            }
            if (i == 0)
                tmpprod.push_back(tmp.substr(printto, index[i] - printto));
            else
                tmpprod.push_back(tmp.substr(printto + 1, index[i] - printto - 1));
        }
        string lastPush = tmp.substr(index[index.size()-1] + 1, tmp.length() - index[index.size()-1] - 2);
        if (lastPush.substr(lastPush.length()-1, 1) == "\t")
            tmpprod.push_back(tmp.substr(index[index.size()-1] + 1, tmp.length() - index[index.size()-1] - 3));
        else
            tmpprod.push_back(tmp.substr(index[index.size()-1] + 1, tmp.length() - index[index.size()-1] - 2));
        prod.push_back(tmpprod);
    }
    return prod;
}

vector<vector<string>> readTable(string path)
{
    fstream tablefile;
    tablefile.open(path, ios::in);
    string tmp;
    vector<vector<string>> table;
    while(!tablefile.eof())
    {
        getline(tablefile, tmp);
        // cout << tmp << endl << endl << endl;
        vector<string> tmptable;
        vector<int> index;
        for (int i = 0; i < tmp.length(); i++)
            if (tmp.substr(i, 1) == "\t")
                index.push_back(i);
        if (index.size() == 0)
            break;
        for (int i = 0; i < index.size() - 1; i++)
            tmptable.push_back(tmp.substr(index[i] + 1, index[i+1] - index[i] - 1));
        table.push_back(tmptable);
    }
    /*
    for (int i = 0; i < table.size(); i++)
        cout << table[i].size() << endl;
    cout << table.size();
    */
    return table;
}

vector<string> getProd(vector<vector<vector<string>>> prodNow, int a, int b)
{
    vector<string> re;
    re.push_back(prodNow[a][0][0]);
    for (int i = 0; i < prodNow[a][b].size(); i++)
        re.push_back(prodNow[a][b][i]);
    return re;
}

vector<string> Grammar(vector<tokenOut>* tokens, vector<vector<string>> table, vector<vector<string>> prod)
{
    vector<string> new1;
    vector<vector<vector<string>>> prodNow;
    vector<int> stateStack;
    vector<string> tokenVector;
    vector<string> tokenNow;
    int ip;
    
    for (int i = 0; i < prod.size(); i++)
    {
        vector<vector<string>> tmpTableNow;
        tmpTableNow.clear();
        vector<string> ttn;
        for (int j = 0; j < prod[i].size(); j++)
        {
            if (j == 0)
            {
                ttn.push_back(prod[i][j]);
                if (ttn.size() != 0)
                    tmpTableNow.push_back(ttn);
                ttn.clear();
                continue;
            }
            else
            {
                if (prod[i][j] == "")
                {
                    if (ttn.size() != 0)
                        tmpTableNow.push_back(ttn);
                    ttn.clear();
                }
                else if (j == prod[i].size() - 2)
                {
                    ttn.push_back(prod[i][j]);
                    ttn.push_back(prod[i][j+1]);
                    if (ttn.size() != 0)
                    {
                        tmpTableNow.push_back(ttn);
                        ttn.clear();
                    }
                }
                else
                    ttn.push_back(prod[i][j]);
            }
        }
        if (ttn.size() != 0)
        {
            tmpTableNow.push_back(ttn);
            ttn.clear();
        }
        prodNow.push_back(tmpTableNow);
    }
    
    for (int i = 0; i < (*tokens).size(); i++)
    {
        // cout << (*tokens)[i].cate << "\t" << (*tokens)[i].valInt << "\t" << (*tokens)[i].valFloat << "\t" << (*tokens)[i].valString << endl;
        if ((*tokens)[i].cate == 0)
        {
            tokenNow.push_back("IDENTIFIER");
            continue;
        }
        else if ((*tokens)[i].cate == 1 or (*tokens)[i].cate == 2)
        {
            tokenNow.push_back("CONSTANT");
            continue;
        }
        else if ((*tokens)[i].cate == 3)
        {
            tokenNow.push_back("STRING_LITERAL");
            continue;
        }
        else if ((*tokens)[i].cate == 4)
        {
            string tmp = ReservedWord[(*tokens)[i].valInt];
            tokenNow.push_back(toUpper(tmp));
            continue;
        }
        else if ((*tokens)[i].cate >= 10 and (*tokens)[i].cate <= 55)
        {
            int tmp = (*tokens)[i].cate;
            if (tmp == 10)
                tokenNow.push_back("ELLIPSIS");
            else if (tmp == 11)
                tokenNow.push_back("RIGHT_ASSIGN");
            else if (tmp == 12)
                tokenNow.push_back("LEFT_ASSIGN");
            else if (tmp == 13)
                tokenNow.push_back("ADD_ASSIGN");
            else if (tmp == 14)
                tokenNow.push_back("SUB_ASSIGN");
            else if (tmp == 15)
                tokenNow.push_back("MUL_ASSIGN");
            else if (tmp == 16)
                tokenNow.push_back("DIV_ASSIGN");
            else if (tmp == 17)
                tokenNow.push_back("MOD_ASSIGN");
            else if (tmp == 18)
                tokenNow.push_back("AND_ASSIGN");
            else if (tmp == 19)
                tokenNow.push_back("XOR_ASSIGN");
            else if (tmp == 20)
                tokenNow.push_back("OR_ASSIGN");
            else if (tmp == 21)
                tokenNow.push_back("RIGHT_OP");
            else if (tmp == 22)
                tokenNow.push_back("LEFT_OP");
            else if (tmp == 23)
                tokenNow.push_back("INC_OP");
            else if (tmp == 24)
                tokenNow.push_back("DEC_OP");
            else if (tmp == 25)
                tokenNow.push_back("PTR_OP");
            else if (tmp == 26)
                tokenNow.push_back("AND_OP");
            else if (tmp == 27)
                tokenNow.push_back("OR_OP");
            else if (tmp == 28)
                tokenNow.push_back("LE_OP");
            else if (tmp == 29)
                tokenNow.push_back("GE_OP");
            else if (tmp == 30)
                tokenNow.push_back("EQ_OP");
            else if (tmp == 31)
                tokenNow.push_back("NE_OP");
            else if (tmp == 32)
                tokenNow.push_back(";");
            else if (tmp == 33)
                tokenNow.push_back("{");
            else if (tmp == 34)
                tokenNow.push_back("}");
            else if (tmp == 35)
                tokenNow.push_back(",");
            else if (tmp == 36)
                tokenNow.push_back(":");
            else if (tmp == 37)
                tokenNow.push_back("=");
            else if (tmp == 38)
                tokenNow.push_back("(");
            else if (tmp == 39)
                tokenNow.push_back(")");
            else if (tmp == 40)
                tokenNow.push_back("[");
            else if (tmp == 41)
                tokenNow.push_back("]");
            else if (tmp == 42)
                tokenNow.push_back(".");
            else if (tmp == 43)
                tokenNow.push_back("&");
            else if (tmp == 44)
                tokenNow.push_back("!");
            else if (tmp == 45)
                tokenNow.push_back("~");
            else if (tmp == 46)
                tokenNow.push_back("-");
            else if (tmp == 47)
                tokenNow.push_back("+");
            else if (tmp == 48)
                tokenNow.push_back("*");
            else if (tmp == 49)
                tokenNow.push_back("/");
            else if (tmp == 50)
                tokenNow.push_back("%");
            else if (tmp == 51)
                tokenNow.push_back("<");
            else if (tmp == 52)
                tokenNow.push_back(">");
            else if (tmp == 53)
                tokenNow.push_back("^");
            else if (tmp == 54)
                tokenNow.push_back("|");
            else if (tmp == 55)
                tokenNow.push_back("?");
        }
    }
    
    tokenVector.push_back("$");
    for (int i = 0; i < tokenNow.size(); i++)
    {
        tokenVector.push_back(tokenNow[i]);
        // cout << tokenNow[i] << endl;
    }
    tokenVector.push_back("$");
    stateStack.push_back(0);
    ip = 1;
    vector<string> tokenLeft;
    tokenLeft.push_back("$");
    
    while (true)
    {
        cout << "Token:\t";
        for (int i = 0; i < tokenLeft.size(); i++)
            cout << tokenLeft[i] << "\t";
        cout << endl;
        
        cout << "State:\t";
        for (int i = 0; i < stateStack.size(); i++)
            cout << stateStack[i] << "\t";
        cout << endl;
        
        cout << ip << endl << endl;
        
        int s = stateStack.back();
        string a = tokenVector[ip];
        int aIndex = 0;
        for (int i = 0; i < table[0].size(); i++)
        {
            if (table[0][i] == a)
            {
                aIndex = i;
                break;
            }
        }
        if (table[s+1][aIndex][0] == 'S')
        {
            string stateTmp = table[s+1][aIndex];
            // cout << stateTmp.substr(2, stateTmp.length() - 1) << endl;
            int stateTmpInt = atoi(stateTmp.substr(2, stateTmp.length() - 1).c_str());
            stateStack.push_back(stateTmpInt);
            tokenLeft.push_back(tokenVector[ip]);
            if (tokenVector[ip] == "(")
                cout << "\nHello World!" << endl;
            ip++;
            continue;
        }
        else if (table[s+1][aIndex][0] == 'R')
        {
            string stateTmp = table[s+1][aIndex].substr(2, table[s+1][aIndex].length() - 1);
            int tabIndex = 0;
            for (int i = 0; i < stateTmp.length(); i++)
            {
                if (stateTmp[i] == ' ')
                {
                    tabIndex = i;
                    break;
                }
            }
            // cout << stateTmp.substr(0, tabIndex) << "| |" << stateTmp.substr(tabIndex + 1, stateTmp.length()) << endl;
            int m = atoi(stateTmp.substr(0, tabIndex).c_str()), n = atoi(stateTmp.substr(tabIndex + 1, stateTmp.length()).c_str());
            vector<string> loopProd = getProd(prodNow, m, n);
            int lenProd = int(loopProd.size()) - 1;
            for (int i = 0; i < lenProd; i++)
            {
                tokenLeft.pop_back();
                stateStack.pop_back();
            }
            s = stateStack.back();
            string tmpA = loopProd[0];
            for (int i = 0; i < table[0].size(); i++)
            {
                if (table[0][i] == tmpA)
                {
                    tokenLeft.push_back(tmpA);
                    stateStack.push_back(atoi(table[s+1][i].c_str()));
                    for (int i = 0; i < lenProd + 1; i++)
                    {
                        if (i == 0)
                            cout << loopProd[0] << "\t->\n\t";
                        else
                            cout << loopProd[i] << "\t";
                    }
                    cout << endl << endl;
                    break;
                }
            }
        }
        else if (table[s+1][aIndex] == "acc")
        {
            cout << "Successfully Reducted!" << endl;
            return new1;
        }
        else
        {
            cout << "Wrong!" << endl;
            return new1;
        }
    }
    
    return new1;
}
