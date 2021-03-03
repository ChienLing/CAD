#include <bits/stdc++.h>
#include "parser.h"
#include "TableElement.h"
#include "littleP.h"
#include "Petrick.h"
#include "QM.h"
using namespace std;

vector<char> BitArray(int, int);
void print(map<int, map<int, vector<TableElement>>>&);
int countBit1 (int);
int main(int argc, char* argv[]) {

    // if (argc < 2) {
    //     cout<<"Please input file!!\n"; 
    //     return 0;
    // }
    Parser* parser = new Parser;
    // parser->readInputFile(argv[1]);
    parser->readInputFile("input4.txt");
    map<int, map<int, vector<TableElement>>> Table;
    //  column /cluster/     row of cluster
    int idx(0);
    // cout<<"onset size: "<< parser->onSet.size()<<endl;
    cout<<"variable: "<<parser->var<<endl;
    for (int i=0; i<parser->onSet.size(); i++) {
        Table[0][countBit1(*parser->onSet[i].value.begin())].push_back(parser->onSet[i]);
    }

    for (int i=0; i<parser->dcSet.size(); i++) {
        Table[0][countBit1(*parser->dcSet[i].value.begin())].push_back(parser->dcSet[i]);
    }

    vector<tuple<int,int,int>> ID;
    ID = QM(Table);
    // cout<<"Table Size: "<<Table.size()<<"\n";
    // print(Table);

    map<int,vector<littleP>> funcP = P(ID,Table,parser->onSet);
    vector<vector<littleP>> FUNCP;
    // printP_map(funcP);
    for (auto it=funcP.begin(); it!=funcP.end(); it++)
        FUNCP.push_back(it->second);
    Petrick(FUNCP);
    // printP_vector(FUNCP);
    if (argc < 3) 
        cout<<"Please enter output name!\n";
    parser->writeOutputFile("output.txt",ID, Table, FUNCP);

    
}

void print(map<int, map<int, vector<TableElement>>> &Table) {
    int ColumnNum(0);
    for (const auto& column:Table) {//add const cause we dont need to change value///////////////////////////////??????
        cout<<"Column: "<<ColumnNum<<endl;
        int ClusterNum(0);
        for (const auto& cluster:column.second) {
            for (auto idx = cluster.second.begin(); idx != cluster.second.end(); idx++)
                cout<<*idx->value.begin()<<endl;
            ClusterNum++;
        }
        ColumnNum++;
    }
}

int countBit1 (int n) {
    int count(0);
    while(n) {
        n= n&n-1;
        count++;
    }
    return count;
}


