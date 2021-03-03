#ifndef _PETRICK_H_
#define _PETRICK_H_
#include <bits/stdc++.h>
#include "TableElement.h"
#include "littleP.h"

void printP_map(const std::map<int, std::vector<littleP>> &funcP);
void printP_vector(const std::vector<std::vector<littleP>> &funcP);
bool cmpPNum(const std::vector<bool> &vec1, const std::vector<bool> &vec2);
int combineImpli(const std::vector<bool>& vec1, const std::vector<bool>& vec2, std::vector<bool>& result);
map<int, std::vector<littleP>> P (std::vector<tuple<int,int,int>> &ID, std::map<int,map<int, vector<TableElement>>> &Table, vector<TableElement> onSet);

void Petrick (std::vector<std::vector<littleP>> &funcP) {
    int parentheses(0);
    for (int idx=funcP.size()-2; idx>=0; idx--) {//(idx)(idy)
    int idy = idx+1;
    std::cout<<"idy : "<<idx<<"\n";
        vector<littleP> temVec;
        for (int i=0; i<funcP[idx].size(); i++) {
            for (int j=0; j<funcP[idy].size(); j++) {
                if (funcP[idy][j].bit1Num <= funcP[idx][i].bit1Num && cmpPNum(funcP[idy][j].implicant, funcP[idx][i].implicant)) {
                    break;
                }
                littleP temP;
                temP.implicant.resize(funcP[idx][i].implicant.size());
                temP.bit1Num = combineImpli(funcP[idx][i].implicant, funcP[idy][j].implicant, temP.implicant);
                temVec.push_back(temP);
            }
        }
        funcP.pop_back();
        funcP[idx] = temVec;
        bool delPtr1(false);
        int IDX(0);
        for (auto it1=funcP[idx].begin(); it1!=funcP[idx].end();) {//(it1 it2)
            if (IDX%500 == 0)
                std::cout<<"IDX: "<<IDX++<<"\n";
            IDX++;
            delPtr1 = false;
            for (auto it2=it1+1; it2!=funcP[idx].end();) {
                if (it1->bit1Num <= it2->bit1Num) {
                    if (cmpPNum(it1->implicant, it2->implicant)) {
                        it2 = funcP[idx].erase(it2);
                    }
                    else 
                        it2++;
                }
                else if (cmpPNum(it2->implicant, it1->implicant)) {//it1->bit1Num > it2->bit1Num
                    delPtr1 = true;
                    break;
                }
                else
                {
                    it2++;
                }
            }
            if (delPtr1)
                it1 = funcP[idx].erase(it1);
            else
            {
                it1++;
            }
                
        }
    }
}

std::map<int, std::vector<littleP>> P (std::vector<tuple<int,int,int>> &ID, std::map<int,map<int, std::vector<TableElement>>> &Table, std::vector<TableElement> onSet) {
    std::map<int, std::vector<littleP>> funcP;//vector size = ID.size
    std::vector<bool> OnSet(1024,false);
    for (int i=0; i<onSet.size(); i++) {
        OnSet[*onSet[i].value.begin()] = true;
    }
    for (int id=0; id<ID.size(); id++) {//P_id
        for (auto it=Table[get<0>(ID[id])][get<1>(ID[id])][get<2>(ID[id])].value.begin(); it!=Table[get<0>(ID[id])][get<1>(ID[id])][get<2>(ID[id])].value.end(); it++) {
            if (OnSet[*it]) {
                littleP temP;
                temP.implicant.resize(ID.size(),false);
                temP.bit1Num = 1;////////////////??????????????????????

                temP.implicant[id] = true;
                funcP[*it].push_back(temP);
            }
        }
    }
    return funcP;
}

void printP_map(const std::map<int, std::vector<littleP>> &funcP) {
    for (auto it1=funcP.begin(); it1!=funcP.end(); it1++) {
        std::cout<<"onset number: "<<it1->first<<"\n";
        for (auto it2=it1->second.begin(); it2!=it1->second.end(); it2++) {
            for (auto it3=it2->implicant.rbegin(); it3!=it2->implicant.rend(); it3++) {
                std::cout<<*it3<<" ";
            }
            std::cout<<"\n";
        }
    }
}

void printP_vector(const std::vector<std::vector<littleP>> &funcP) {
    for (int i=0; i<funcP.size(); i++) {
        cout<<"parenthese : "<<i<<"\n";
        for (int j=0; j<funcP[i].size(); j++) {
            cout<<"item: "<<j<<"\n";
            for (auto it3=funcP[i][j].implicant.rbegin(); it3!=funcP[i][j].implicant.rend(); it3++) {
                std::cout<<*it3<<" ";
            }
            std::cout<<"\n";
        }
    }
}

int combineImpli(const std::vector<bool>& vec1, const std::vector<bool>& vec2, std::vector<bool>& result) {
    int count(0);
    for (int i=0; i<vec1.size(); i++) {
        result[i] = vec2[i]|vec1[i];
        if (result[i])
            count++;
    }
    return count;
}

bool cmpPNum(const std::vector<bool> &vec1, const std::vector<bool> &vec2) {
    for (int i=0; i<vec1.size(); i++) {
        if (vec1[i] && vec1[i]!=vec2[i])
            return false;
    }
    return true;
}
#endif