#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <bits/stdc++.h>
struct vertex {
    bool source;
    bool sink;
    bool outputValue;
    bool controling;
    int parent;
    int inputNum;
    double gateDelay;
    double sensiDelay;
    double outputCapacity;
    double inputCapacity1;
    double inputCapacity2;
    double inputTransTime;
    double outputTransTime;
    std::string gateName;
    std::vector<int> OutAdjacencyList;
    std::vector<int> InAdjacencyList;
    std::vector<int> inputNet;
    std::vector<int> outputNet;
    vertex():source(false), sink(false), outputValue(false), controling(false), parent(0), inputNum(0), gateDelay(0), sensiDelay(0), outputCapacity(0), inputTransTime(0), inputCapacity1(0), inputCapacity2(0), outputTransTime(0){}
};
#endif