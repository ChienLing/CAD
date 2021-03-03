#ifndef _QM_H_
#define _QM_H_
#include <bits/stdc++.h>
#include "TableElement.h"

int compare(const int& a,const int& b);
bool cmpHyphen(const std::set<int>& , const std::set<int> &);
vector<tuple<int,int,int>> QM(std::map<int, std::map<int, std::vector<TableElement>>>& Table) {
    // map<int,TableElement> implicant

    vector<tuple<int,int,int>> ID;
    int column(0);
    int TE1value(0), TE2value(0);
    bool newCloumn(true);
    while (newCloumn) {
        newCloumn = false;
        int cluster(0);
        for (int i=0; i<Table[column].size()-1; i++) {//cluster from 0 to #cluster-1 
            bool newCluster(false);
            int j(0);//# next column cluster 
            for (auto& TE1:Table[column][i]) {//implicant in Table[column][cluster]
            TE1value = *TE1.value.begin();
                for (auto& TE2:Table[column][i+1]) {
                    TE2value = *TE2.value.begin();
                    // for (int idx=0; idx<TE1.hyphenPos.size(); idx++) {//compare hyphen position
                    bool hyphenEqual = cmpHyphen(TE1.hyphenPos, TE2.hyphenPos);
                    if (hyphenEqual) {
                        int pos = compare(*TE1.value.begin(), *TE2.value.begin());//pos = position of different bit
                        if (pos >= 0) {
                            newCluster = true;//have new cluster
                            newCloumn = true;
                            TableElement TE;
                            TE.hyphenPos.insert(TE1.hyphenPos.begin(),TE1.hyphenPos.end());
                            TE.value.insert(TE1.value.begin(),TE1.value.end());
                            TE.value.insert(TE2.value.begin(),TE2.value.end());
                            TE.hyphenPos.insert(pos);
                            TE1.merged = true;
                            TE2.merged = true;
                            bool InsertTE(true);
                            for (int idx=0; idx<Table[column+1][cluster].size(); idx++) {
                                if(Table[column+1][cluster][idx] == TE) {
                                    InsertTE = false;
                                    break;
                                }
                            }
                            if (InsertTE)
                                Table[column+1][cluster].push_back(TE);
                        }
                    }
                    
                }
                if (!TE1.merged) {
                    ID.push_back({column,i,j});
                }
                j++;
            }
            if (newCluster)
                cluster++;
            if (i == Table[column].size()-2) {
                for (int j=0; j<Table[column].rbegin()->second.size(); j++) {
                    if (!Table[column][Table[column].size()-1][j].merged)
                        ID.push_back({column,Table[column].size()-1,j});
                }       
            }
        }
        column++;
    }
    // for (int i=0; i<Table.size(); i++) {
    //     for (int j=0; j<Table[i].rbegin()->second.size(); j++) {
    //         if (!Table[i][Table[i].size()-1][j].merged)
    //             ID.push_back({i,Table[i].size()-1,j});
    //     }
    // }
    return ID;
}

int compare(const int &a, const int &b) {///////////////////////
    bitset<10> A(a), B(b), C;
    C = A ^ B;
    if (C.count() != 1)
        return -1;
    for (int i=0; i<10; i++) {
        if (C[i] == 1)
            return i;
    }
}
bool cmpHyphen(const std::set<int>& H1, const std::set<int> & H2) {
    std::set<int>::const_iterator idy;
    std::set<int>::const_iterator idx;
    for (idx=H1.begin(), idy=H2.begin(); idx!=H1.end(); idx++, idy++) {
        if (*idx != *idy)
            return false;
    }
    return true;
}
#endif