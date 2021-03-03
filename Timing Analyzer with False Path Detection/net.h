#ifndef _NET_H_
#define _NET_H_
#include <bits/stdc++.h>
struct net {
    bool netValue;
    std::set<int> InGate;// dosent need use set
    std::set<int> OutGate;
    net():netValue(false){}
};
#endif