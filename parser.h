#ifndef _PARSER_H_
#define _PARSER_H_
#include <bits/stdc++.h>
#include "TableElement.h"
#include "littleP.h"
using namespace std;
class Parser {
    
    public:

    std::vector<TableElement> onSet, dcSet;
    std::string InFileName;
    std::string OutFileName;
    std::ifstream input;
    std::ofstream output;
    int var;


    Parser() {}
    Parser(std::string s);
    void readInputFile();
    void readInputFile(const std::string fileName);
    int printImplicant(const tuple<int,int,int> &idx, std::map<int, std::map<int, std::vector<TableElement>>> &Table);
    void writeOutputFile(const std::string fileName, const std::vector<tuple<int,int,int>> &ID,  std::map<int, std::map<int, std::vector<TableElement>>> &Table, const std::vector<std::vector<littleP>>& funcP);
};

/////////////////////////////Constructor//////////////////////////////
Parser::Parser(std::string s):InFileName(s) {
    }

//////////////////////////////Read File///////////////////////////////
void Parser::readInputFile(const std::string fileName) {
    int dcterm, minterm;
    std::string trash, S;
    // std::cout<<"file name: "<<fileName<<"\n";
    InFileName = fileName;
    input.open(InFileName);
    if(!input) {    //test if file opened 
        std::cerr << "Can't open "<<fileName<<"!\n";
        exit(1);     //if unusual, close it 
    }

    getline(input,S); 
    {
        std::stringstream SS(S);
        SS>>trash>>var;
    }
    // std::cout<<"var: "<<var<<"\n";
    getline(input,S);
    getline(input,S);
    {
        std::stringstream SS(S);
        while (SS>>minterm){
            TableElement TE;
            TE.value.insert(minterm);
            onSet.push_back(TE);
        }
    }
    // std::cout<<"On Set:\n";
    // for (int i=0; i<onSet.size(); i++) {
    //     std::cout<<*onSet[i].value.begin()<<" ";
    // }
    getline(input,S);
    getline(input,S);
    std::stringstream SS(S);
    while (SS>>dcterm) {
        TableElement TE;
        TE.value.insert(dcterm);
        dcSet.push_back(TE);
    }
    // std::cout<<"\ndc set\n";
    // for (int i=0; i<dcSet.size(); i++) {
    //     std::cout<<*dcSet[i].value.begin()<<" ";
    // }
    // std::cout<<"\n";
    return;
}

void Parser::readInputFile() {
    int dcterm, minterm;
    std::string trash, S;
    // std::cout<<"file name: "<<InFileName<<"/"<<"\n";
    input.open(InFileName);
    if(!input) {    //test if file opened 
        std::cerr << "Can't open "<<InFileName<<"!\n";
        exit(1);     //if unusual, close it 
    }

    getline(input,S); 
    {
        std::stringstream SS(S);
        SS>>trash>>var;
    }
    // std::cout<<"var: "<<var<<"\n";
    getline(input,S);
    getline(input,S);
    {
        std::stringstream SS(S);
        while (SS>>minterm){
            std::cout<<minterm<<"\n";
            TableElement TE;
            TE.value.insert(minterm);
            onSet.push_back(TE);
        }
    }
    // std::cout<<"On Set:\n";
    // for (int i=0; i<onSet.size(); i++) {
    //     std::cout<<*onSet[i].value.begin()<<" ";
    // }
    getline(input,S);
    getline(input,S);
    std::stringstream SS(S);
    while (SS>>dcterm) {
        TableElement TE;
        TE.value.insert(dcterm);
        dcSet.push_back(TE);
    }
    // std::cout<<"\ndc set\n";
    // for (int i=0; i<dcSet.size(); i++) {
        //std::cout<<*dcSet[i].value.begin()<<" ";
    // }
    // std::cout<<"\n";
    return;
}
///////////////////////////////Output File/////////////////////////////
void Parser::writeOutputFile(const std::string fileName, const std::vector<tuple<int,int,int>> &ID,
    std::map<int, std::map<int, std::vector<TableElement>>> &Table, const std::vector<std::vector<littleP>>& funcP) {

    OutFileName = fileName;
    output.open(OutFileName);
    std::set<int>::iterator it;
    output<<".pi "<<ID.size()<<"\n";
    // std::cout<<".pi "<<ID.size()<<"\n";
    if (ID.size() > 20) {
        for (int i=ID.size()-1; i>=ID.size()-20; i--)
            printImplicant(ID[i],Table);
    }
    else
    {
        for (int i=0; i<ID.size(); i++) 
            printImplicant(ID[i],Table);
    }
    
    
    int MinImpli(INT32_MAX);
    int MinInpliItem(0);
    for (int i=0; i<funcP[0].size(); i++) {
        if (funcP[0][i].bit1Num < MinImpli) {
            MinImpli = funcP[0][i].bit1Num;
            MinInpliItem = i;
        }
    }
    output<<"mc. "<<MinImpli<<"\n";///////////////////////////////////////////
    // std::cout<<"mc. "<<MinImpli<<"\n";
    int count(0);
    for (int i=0; i<funcP[0][MinInpliItem].implicant.size(); i++) {
        if (funcP[0][MinInpliItem].implicant[i]) {
            count += printImplicant(ID[i],Table);
        }
    }
    
    output<<"cost="<<count<<"\n";
    // cout<<"cost="<<count<<"\n";
    output.close();
}

int Parser::printImplicant(const tuple<int,int,int>& idx, std::map<int,std::map<int, std::vector<TableElement>>>& Table) {
    std::set<int>::iterator it;
    int count(0);
    // if (Table[get<0>(idx)][get<1>(idx)][get<2>(idx)].hyphenPos.size() != 0)
    it = Table[get<0>(idx)][get<1>(idx)][get<2>(idx)].hyphenPos.begin();
    int CurValue = *Table[get<0>(idx)][get<1>(idx)][get<2>(idx)].value.begin();
    vector<int> vec(var);
    for (int i=0; i<var; i++) {
        if (it!=Table[get<0>(idx)][get<1>(idx)][get<2>(idx)].hyphenPos.end() && *it == i) {
            vec[i] = 2;
            CurValue = CurValue>>1;
            it++;
        }
        else {
            count++;
            if (CurValue&1)
                vec[i] = 1;
            else 
                vec[i] = 0;
            CurValue = CurValue>>1;
        }
    }
    for (int i=var-1; i>=0; i--) {
        if (vec[i] == 0) {
            output<<"0";
            // std::cout<<"0";
        }
        else if (vec[i] == 1) {
            output<<"1";
            // std::cout<<"1";
        }
        else {
            output<<"-";
            // std::cout<<"-";
        }
    }
    // std::cout<<"\n";
    output<<"\n";
    return count;
}
#endif