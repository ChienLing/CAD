#ifndef _TABLEELEMENT_H_
#define _TABLEELEMENT_H_
#include <bits/stdc++.h>
struct TableElement {
    std::set<int> hyphenPos;
    std::set<int> value;
    bool merged;
    TableElement(void):merged(false) {}
    bool operator < (const TableElement &TE) const {
        return *value.begin() < *TE.value.begin();
    } 
    bool operator > (const TableElement &TE) const {
        return *value.begin() > *TE.value.begin();
    } 
    
    bool operator == (const TableElement &TE) const {
        std::set<int>::iterator it1(NULL);
        std::set<int>::iterator it2{NULL};
        if (hyphenPos.size() == TE.hyphenPos.size() && value.size() == TE.value.size() && merged == TE.merged) {
            for (it1=hyphenPos.begin(), it2 = TE.hyphenPos.begin(); it1!=hyphenPos.end(); it1++, it2++) {
                if (*it1!=*it2)
                    return false;
            }
            for (it1=value.begin(), it2=TE.value.begin(); it1!=value.end(); it1++,it2++) {
                if (*it1!=*it2)
                    return false;
            }
            return true;
        }
        return false;
    } 
    void printTE(const TableElement& TE) const{
        std::cout<<"value:\n";
        for (auto i=value.begin(); i!=value.end(); i++) {
            std::cout<<*i<<" ";
        }
        std::cout<<"\nhyphen position:\n";
        for (auto i=hyphenPos.begin(); i!=hyphenPos.end(); i++) {
            std::cout<<*i<<" ";
        }
        std::cout<<"\n";
    }
};
#endif