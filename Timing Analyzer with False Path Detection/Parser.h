#ifndef _PARSER_H_
#define _PARSER_H_
#include <bits/stdc++.h>
#include "vertex.h"
#include "net.h"

class Parser {
    public:
    std::ifstream LibInput, vInput;
    std::ofstream output;
    std::string vFileName, libFileName, patFileName, outputFileName;
    std::map<std::string,int> vertexNum;
    std::map<int,std::string> vertexName;
    std::map<std::string,int> netNum;
    std::map<int,std::string> netName;
    std::vector<vertex> VertexVector;
    std::vector<net> NetVector;
    std::vector<std::vector<int>> noInputGate;
    std::vector<int> outputGate;
    std::vector<double> index1;//capacity
    std::vector<double> index2;//transition time

    /////////////////////            NOR             /////////////////////////
    double NOR2x1_In1, NOR2x1_In2, NOR2x1_Out1;
    std::vector<std::vector<double>> NOR2x1_RisePower;
    std::vector<std::vector<double>> NOR2x1_FallPower; 
    std::vector<std::vector<double>> NOR2x1_CellRise; 
    std::vector<std::vector<double>> NOR2x1_CellFall; 
    std::vector<std::vector<double>> NOR2x1_RiseTransition; 
    std::vector<std::vector<double>> NOR2x1_FallTransition; 
    /////////////////////            Invertor             /////////////////////////
    double INV1x1_In1, INV1x1_Out1;
    std::vector<std::vector<double>> INV1x1_RisePower; 
    std::vector<std::vector<double>> INV1x1_FallPower; 
    std::vector<std::vector<double>> INV1x1_CellRise; 
    std::vector<std::vector<double>> INV1x1_CellFall; 
    std::vector<std::vector<double>> INV1x1_RiseTransition; 
    std::vector<std::vector<double>> INV1x1_FallTransition; 
    /////////////////////              NAND              //////////////////////////
    double NAND2x1_In1, NAND2x1_In2, NAND2x1_Out1;
    std::vector<std::vector<double>> NAND2x1_RisePower; 
    std::vector<std::vector<double>> NAND2x1_FallPower; 
    std::vector<std::vector<double>> NAND2x1_CellRise; 
    std::vector<std::vector<double>> NAND2x1_CellFall; 
    std::vector<std::vector<double>> NAND2x1_RiseTransition; 
    std::vector<std::vector<double>> NAND2x1_FallTransition; 

    /////////////////////////           Function           ///////////////////////////
    Parser();
    void readV();
    void readLib();
    void readFile(const std::string, const std::string);
    void readTable(std::vector<std::vector<double>>&);
    void readInput(const std::string);
    void calWeight();
    void calCapacity();
    void calOutput();
    void calTiming();
    void TopologicalSort();
    int findIndex(std::vector<double>& vec, double cmpValue);
    void UpdateAdjacency();
    double Interpolation(std::vector<std::vector<double>> Table, int gateNum);
    void longestPath();//////////////////
    void printOrder();
    void printV();
    void printNet();
    void printIndex();
    void printTable(std::vector<std::vector<double>>&);
    void printLongestPath();
    void reset();
    void printNormalForm();
    void openOutput();
};

Parser::Parser(){}

void Parser::longestPath() {
    for (int i=1; i<noInputGate.size(); i++) {
        for (auto gate=noInputGate[i].begin(); gate!=noInputGate[i].end(); gate++) {
            double path(0);
            if (VertexVector[*gate].gateName == "INVX1") {
                VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay;
                VertexVector[*gate].parent = *VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputNet.begin();
            }
            else if (VertexVector[*gate].gateName == "NANDX1") {
                if (!VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputValue && 
                    !VertexVector[VertexVector[*gate].InAdjacencyList[1]].outputValue) {// all controling
                        if (VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay < VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay) {
                            VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay;
                            VertexVector[*gate].parent = VertexVector[*gate].inputNet[0];
                            VertexVector[*gate].controling = false;
                        }
                        else {
                            VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay;
                            VertexVector[*gate].parent = VertexVector[*gate].inputNet[1];
                            VertexVector[*gate].controling = true;
                        }
                        
                    }
                else if (!VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputValue) {//input 0 controling
                    VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay;
                    VertexVector[*gate].parent = VertexVector[*gate].inputNet[0];
                            VertexVector[*gate].controling = false;
                }
                else if (!VertexVector[VertexVector[*gate].InAdjacencyList[1]].outputValue) {///input 0 controling
                    VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay;
                    VertexVector[*gate].parent = VertexVector[*gate].inputNet[1];
                            VertexVector[*gate].controling = true;
                }
                else {
                    if (VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay > VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay) {
                            VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay;
                            VertexVector[*gate].parent = VertexVector[*gate].inputNet[0];
                            VertexVector[*gate].controling = false;
                        }
                        else {
                            VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay;
                            VertexVector[*gate].parent = VertexVector[*gate].inputNet[1];
                            VertexVector[*gate].controling = true;
                        }

                }
            }
            else if (VertexVector[*gate].gateName == "NOR2X1") {
                if (VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputValue && 
                    VertexVector[VertexVector[*gate].InAdjacencyList[1]].outputValue) {// all controling
                        if (VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay < VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay) {
                            VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay;
                            VertexVector[*gate].parent = VertexVector[*gate].inputNet[0];
                            VertexVector[*gate].controling = false;
                        }
                        else {
                            VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay;
                            VertexVector[*gate].parent = VertexVector[*gate].inputNet[1];
                            VertexVector[*gate].controling = true;
                        }
                        
                    }
                else if (VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputValue) {//input 0 controling
                    VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay;
                    VertexVector[*gate].parent = VertexVector[*gate].inputNet[0];
                            VertexVector[*gate].controling = false;
                }
                else if (VertexVector[VertexVector[*gate].InAdjacencyList[1]].outputValue) {///input 0 controling
                    VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay;
                    VertexVector[*gate].parent = VertexVector[*gate].inputNet[1];
                            VertexVector[*gate].controling = true;
                }
                else {
                    if (VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay > VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay) {
                            VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[0]].sensiDelay;
                            VertexVector[*gate].parent = VertexVector[*gate].inputNet[0];
                            VertexVector[*gate].controling = false;
                        }
                        else {
                            VertexVector[*gate].sensiDelay = VertexVector[*gate].gateDelay + VertexVector[VertexVector[*gate].InAdjacencyList[1]].sensiDelay;
                            VertexVector[*gate].parent = VertexVector[*gate].inputNet[1];
                            VertexVector[*gate].controling = true;
                        }

                }
            }
            else if (VertexVector[*gate].gateName == "output") {
                VertexVector[*gate].sensiDelay = VertexVector[*VertexVector[*gate].InAdjacencyList.begin()].sensiDelay;
            }
            
            // VertexVector[*gate].gateDelay += path;
        }
    }
}

void Parser::readInput(const std::string inputFile) {
    std::ifstream input(inputFile);
    patFileName = inputFile;
    if(!input) {    //test if file opened 
        std::cerr << "Can't open "<<inputFile<<"!\n";
        exit(1);     //if unusual, close it 
    }
    std::vector<int> inputGate;
    std::string code, line, trash;
    while (getline(input, line,','))
        code += line;
    size_t pos=code.find(".end");
    code.erase(pos-1,5);
    std::stringstream SS1(code);
    std::string net;
    {
        getline(SS1,line);
        std::stringstream SS2(line);
        SS2>>trash;
        while (SS2>>net) {
            inputGate.push_back(vertexNum[net]);
        }
    }
    openOutput();
    while (getline(SS1,line)) {
        std::stringstream SS2(line);
        for (int i=0; i<inputGate.size(); i++) {
            bool value;
            SS2>>value;
            VertexVector[inputGate[i]].outputValue = value;
        }
        calTiming();
    }
    output.close();
}

void Parser::calTiming() {
    calOutput();
    calWeight();
    longestPath();
    printLongestPath();
    printNormalForm();
    // writeOutput();
    reset();
}

void Parser::reset() {
    for (int i=0; i<VertexVector.size(); i++) {
        VertexVector[i].gateDelay = 0;
        VertexVector[i].sensiDelay = 0;
        VertexVector[i].inputTransTime = 0;
        VertexVector[i].outputTransTime = 0;
    }
}

void Parser::calOutput() {
    for (int i=1; i<noInputGate.size(); i++) {
        for (auto gate=noInputGate[i].begin(); gate!=noInputGate[i].end(); gate++) {
            if (VertexVector[*gate].gateName == "INVX1") {
                VertexVector[*gate].outputValue = !VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputValue;
            }

            else if (VertexVector[*gate].gateName == "NOR2X1") {// A' and B'
                VertexVector[*gate].outputValue = !VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputValue 
                                                & !VertexVector[VertexVector[*gate].InAdjacencyList[1]].outputValue;
            }

            else if (VertexVector[*gate].gateName == "NANDX1") {// A' or B'
                VertexVector[*gate].outputValue = !VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputValue 
                                                | !VertexVector[VertexVector[*gate].InAdjacencyList[1]].outputValue;
            }
            else if (VertexVector[*gate].gateName == "output") {
                VertexVector[*gate].outputValue = VertexVector[VertexVector[*gate].InAdjacencyList[0]].outputValue;
            }
        }
    }
}

int Parser::findIndex (std::vector<double>& vec, double cmpValue) {
    for (int i=1; i<vec.size(); i++) {
        if (vec[i] >= cmpValue){
            return i-1;
        }
    }
    return vec.size()-2;
}

double Parser::Interpolation(std::vector<std::vector<double>> Table, int gateNum) {
    int index1_Idx = findIndex(index1, VertexVector[gateNum].outputCapacity);
    int index2_Idx = findIndex(index2, VertexVector[gateNum].inputTransTime);
    double A(0), B(0), Preq(0);
    double S2, S1, Sreq;
    double C2, C1, Creq;
    double P0, P1, P2, P3;
    S1 = index2[index2_Idx];
    S2 = index2[index2_Idx+1];
    Sreq = VertexVector[gateNum].inputTransTime;
    P0 = Table[index2_Idx][index1_Idx];
    P1 = Table[index2_Idx+1][index1_Idx];
    P2 = Table[index2_Idx][index1_Idx+1];
    P3 = Table[index2_Idx+1][index1_Idx+1];
    C1 = index1[index1_Idx];
    C2 = index1[index1_Idx+1];
    Creq = VertexVector[gateNum].outputCapacity;
    if (S2 != Sreq) {
        double a=(P1-P0);
        double b=(Sreq-S1);
        double c=(S2-S1);
        double aa=(P1-P3);
        double bb=(Sreq-S1);
        double d=(P1-P0)*(Sreq-S1)/(S2-S1);
        double e=(P1-P3)*(Sreq-S1)/(S2-S1);
        A = P0 + (P1-P0)*(Sreq-S1)/(S2-S1);
        B = P2 + (P3-P2)*(Sreq-S1)/(S2-S1);
        double cc=(S2-S1);

    }
    else {
        A = P1;
        B = P3;
    }
    if (C2!=Creq) {
        Preq = A + (B-A)*(Creq-C1)/(C2-C1);
    }
    else {
        Preq = B;
    }
    return Preq;
}

void Parser::calWeight() {
    for (int i=1; i<noInputGate.size(); i++) {
        for (auto gate=noInputGate[i].begin(); gate!=noInputGate[i].end(); gate++) {
            // std::cout<<VertexVector[*gate].gateName<<"\n";//////////////////////
            if (VertexVector[*gate].gateName == "output")
                continue;
            for (auto fowardGate=VertexVector[*gate].InAdjacencyList.begin(); fowardGate!=VertexVector[*gate].InAdjacencyList.end(); fowardGate++) {
                if (VertexVector[*fowardGate].outputTransTime > VertexVector[*gate].inputTransTime)
                    VertexVector[*gate].inputTransTime = VertexVector[*fowardGate].outputTransTime;
            }
            if (VertexVector[*gate].outputValue) {
                if (VertexVector[*gate].gateName == "INVX1") {
                    VertexVector[*gate].outputTransTime = Interpolation(INV1x1_RiseTransition, *gate);
                    VertexVector[*gate].gateDelay = Interpolation(INV1x1_CellRise, *gate);
                }
                else if (VertexVector[*gate].gateName == "NANDX1") {
                    VertexVector[*gate].outputTransTime = Interpolation(NAND2x1_RiseTransition, *gate);
                    VertexVector[*gate].gateDelay = Interpolation(NAND2x1_CellRise, *gate);
                }
                else if (VertexVector[*gate].gateName == "NOR2X1") {
                    VertexVector[*gate].outputTransTime = Interpolation(NOR2x1_RiseTransition, *gate);
                    VertexVector[*gate].gateDelay = Interpolation(NOR2x1_CellRise, *gate);
                }
            }
            else {
                if (VertexVector[*gate].gateName == "INVX1") {
                    VertexVector[*gate].outputTransTime = Interpolation(INV1x1_FallTransition, *gate);
                    VertexVector[*gate].gateDelay = Interpolation(INV1x1_CellFall, *gate);
                }
                else if (VertexVector[*gate].gateName == "NANDX1") {
                    VertexVector[*gate].outputTransTime = Interpolation(NAND2x1_FallTransition, *gate);
                    VertexVector[*gate].gateDelay = Interpolation(NAND2x1_CellFall, *gate);
                }
                else if (VertexVector[*gate].gateName == "NOR2X1") {
                    VertexVector[*gate].outputTransTime = Interpolation(NOR2x1_FallTransition, *gate);
                    VertexVector[*gate].gateDelay = Interpolation(NOR2x1_CellFall, *gate);
                }
            }
        }
    }
    for (int i=1; i<noInputGate.size(); i++) {
        for (auto gate=noInputGate[i].begin(); gate!=noInputGate[i].end(); gate++) {
            for (auto fowardGate=VertexVector[*gate].InAdjacencyList.begin(); fowardGate!=VertexVector[*gate].InAdjacencyList.end(); fowardGate++) {
                if (VertexVector[*fowardGate].outputTransTime > VertexVector[*gate].inputTransTime)
                    VertexVector[*gate].inputTransTime = VertexVector[*fowardGate].outputTransTime;
            }
        }
    }
    // printV();
}

void Parser::UpdateAdjacency() {
    for (auto gate=VertexVector.begin(); gate!=VertexVector.end(); gate++) {
        for (auto inputNet=gate->inputNet.begin(); inputNet!=gate->inputNet.end(); inputNet++) {
            gate->InAdjacencyList.push_back(*NetVector[*inputNet].InGate.begin());
        }
        auto outputNet=gate->outputNet.begin(); 
        if (outputNet!=gate->outputNet.end()) {
            for (auto nextGate=NetVector[*outputNet].OutGate.begin(); nextGate!=NetVector[*outputNet].OutGate.end(); nextGate++) {
                gate->OutAdjacencyList.push_back(*nextGate);
            }
        }
    }
}

void Parser::TopologicalSort() {
    bool tag(true);
    while(tag) {
        tag = false;
        int idx=noInputGate.size();
        noInputGate.resize(noInputGate.size()+1);
        for (auto gate=noInputGate[idx-1].begin(); gate!=noInputGate[idx-1].end(); gate++) {
            for (auto NextGate=VertexVector[*gate].OutAdjacencyList.begin(); NextGate!=VertexVector[*gate].OutAdjacencyList.end(); NextGate++) {
                VertexVector[*NextGate].inputNum--;
                if (VertexVector[*NextGate].inputNum == 0) {
                    tag = true;
                    noInputGate[idx].push_back(*NextGate);
                }
            } 
        }
    }
    // printOrder();
}

void Parser::calCapacity() {
    for (int i=0; i<NetVector.size(); i++) {
        for (auto itO=NetVector[i].OutGate.begin(); itO!=NetVector[i].OutGate.end(); itO++) {
            if (VertexVector[*itO].inputNet[0] == i)//inputA1 
                VertexVector[*NetVector[i].InGate.begin()].outputCapacity += VertexVector[*itO].inputCapacity1;
            else if (VertexVector[*itO].inputNet[1] == i) 
                VertexVector[*NetVector[i].InGate.begin()].outputCapacity += VertexVector[*itO].inputCapacity2;
        }
    }
}

void Parser::readV() {
    noInputGate.resize(1);
    std::string code, tmpcode, trash, line, str;
    int netIdx(0), vertexIdx(0);
    while (getline(vInput, tmpcode, '/')) {
        code += tmpcode;
        if (vInput.peek() == '/') {
            getline(vInput, trash);
        }
        else if (vInput.peek() == '*')// read /*
        {
            vInput.get();
            getline(vInput, trash, '*');
            vInput.get();
        }
    }

    std::size_t found = code.find_first_of(",()");
    while (found != std::string::npos) {
        code[found] = ' ';
        found = code.find_first_of(",()", found+1);
    }
    std::stringstream SS(code);
    while (getline(SS, line, ';')) {
        SS.get();
        std::stringstream SS2(line);
        SS2>>str;
        // std::cout<<str<<"\n";
        if (str == "output") {
            while (SS2>>str) {
                // std::cout<<str<<"\n";
                net n;
                vertex v;
                outputGate.push_back(vertexIdx);
                v.sink = true;
                v.gateName = "output";
                v.inputCapacity1 = 0.03;
                v.inputNet.push_back(netIdx);
                v.inputNum++;
                n.OutGate.insert(vertexIdx);
                NetVector.push_back(n);
                VertexVector.push_back(v);
                vertexName[vertexIdx] = str;
                vertexNum[str] = vertexIdx++;
                netName[netIdx] = str;
                netNum[str] = netIdx++;
            }
        }
        else if (str == "input") {
            while (SS2>>str) {
                // std::cout<<str<<"\n";
                net n;
                vertex v;
                v.gateName = "input";
                v.source = true;
                v.inputTransTime = 0;
                v.outputNet.push_back(netIdx);
                n.InGate.insert(vertexIdx);
                NetVector.push_back(n);
                VertexVector.push_back(v);
                netName[netIdx] = str;
                noInputGate[0].push_back(vertexIdx);
                netNum[str] = netIdx++;
                vertexName[vertexIdx] = str;
                vertexNum[str] = vertexIdx++;
            }
                // printV();
                // system("pause");
        }
        else if (str == "wire") {
            while (SS2>>str) {
                // std::cout<<str<<"\n";
                netName[netIdx] = str;
                netNum[str] = netIdx++;
                NetVector.resize(netIdx);
            }
            
                // printV();
        }
        else if (str == "INVX1") {
            std::string gateName;
            SS2>>gateName;
            vertex v;
            v.inputNum = 1;
            v.inputCapacity1 = INV1x1_In1;
            v.gateName = "INVX1";
            v.inputNet.resize(1);
            for (int i=0; i<2; i++) {
                SS2>>str;
                if (str==".I") {
                    SS2>>str;
                    v.inputNet[0] = netNum[str];
                    NetVector[netNum[str]].OutGate.insert(vertexIdx);
                }
                else if (str==".ZN") {
                    SS2>>str;
                    v.outputNet.push_back(netNum[str]);
                    NetVector[netNum[str]].InGate.insert(vertexIdx);
                }
            }
            VertexVector.push_back(v);
            vertexName[vertexIdx] = gateName;
            vertexNum[gateName] = vertexIdx++;
            // printV();
        }
        else if (str == "NANDX1") {
            std::string gateName;
            SS2>>gateName;
            // std::cout<<gateName<<"\n";

            vertex v;
            v.gateName = "NANDX1";
            v.inputNum = 2;
            v.inputCapacity1 = NAND2x1_In1;
            v.inputCapacity2 = NAND2x1_In2;
            v.inputNet.resize(2);
            for (int i=0; i<3; i++) {
                SS2>>str;
                if (str==".A1") {
                    SS2>>str;
                    v.inputNet[0] = netNum[str];
                    NetVector[netNum[str]].OutGate.insert(vertexIdx);
                }
                else if (str == ".A2") {
                    SS2>>str;
                    v.inputNet[1] = netNum[str];
                    NetVector[netNum[str]].OutGate.insert(vertexIdx);
                }
                else if (str == ".ZN") {
                    SS2>>str;
                    v.outputNet.push_back(netNum[str]);
                    NetVector[netNum[str]].InGate.insert(vertexIdx);
                }
            }
            VertexVector.push_back(v);
            vertexName[vertexIdx] = gateName;
            vertexNum[gateName] = vertexIdx++;
            // printV();
        }
        else if (str == "NOR2X1") {
            std::string gateName;
            SS2>>gateName;
            vertex v;
            v.gateName = "NOR2X1";
            v.inputNet.resize(2);
            v.inputNum = 2;
            v.inputCapacity1 = NOR2x1_In1;
            v.inputCapacity2 = NOR2x1_In2;
            for (int i=0; i<3; i++) {
                SS2>>str;
                if (str == ".A1") {
                    SS2>>str;
                    v.inputNet[0]=netNum[str];
                    NetVector[netNum[str]].OutGate.insert(vertexIdx);
                }
                else if (str == ".A2") {
                    SS2>>str;
                    v.inputNet[1]=netNum[str];
                    NetVector[netNum[str]].OutGate.insert(vertexIdx);
                    
                }
                else if (str == ".ZN") {
                    SS2>>str;
                    v.outputNet.push_back(netNum[str]);
                    NetVector[netNum[str]].InGate.insert(vertexIdx);
                }
            }
            VertexVector.push_back(v);
            vertexName[vertexIdx] = gateName;
            vertexNum[gateName] = vertexIdx++;
            // printV();
        }
    }
}

void Parser::readLib() {
    index1.resize(7);
    index2.resize(7);
    NOR2x1_RisePower.resize(7); 
    NOR2x1_FallPower.resize(7); 
    NOR2x1_CellRise.resize(7); 
    NOR2x1_CellFall.resize(7); 
    NOR2x1_RiseTransition.resize(7); 
    NOR2x1_FallTransition.resize(7); 


    INV1x1_RisePower .resize(7); 
    INV1x1_FallPower .resize(7); 
    INV1x1_CellRise .resize(7); 
    INV1x1_CellFall .resize(7); 
    INV1x1_RiseTransition .resize(7); 
    INV1x1_FallTransition .resize(7); 

    NAND2x1_RisePower .resize(7); 
    NAND2x1_FallPower .resize(7); 
    NAND2x1_CellRise .resize(7); 
    NAND2x1_CellFall .resize(7); 
    NAND2x1_RiseTransition .resize(7); 
    NAND2x1_FallTransition .resize(7); 

    std::string S, trash;
    bool skip(false);
    for (int i=0; i<9; i++) {
        getline(LibInput,S);
    }
    {
        getline(LibInput,S,'"');       getline(LibInput,S,'"');       getline(LibInput,trash);
        std::stringstream SS(S);
        for (int i=0; i<7; i++) {
            getline(SS,S,',');
            std::stringstream SS2(S);
            SS2>>index1[i];
        }
    }
    {
        getline(LibInput,S,'"');       getline(LibInput,S,'"');       getline(LibInput,trash);
        std::stringstream SS(S);
        for (int i=0; i<7; i++) {
            getline(SS,S,',');
            std::stringstream SS2(S);
            SS2>>index2[i];
        }
    }
    for (int i=0; i<7; i++)
        getline(LibInput,S);
    {
        std::stringstream SS(S);
        SS>>S>>S>>S;
        std::stringstream SS2(S);
        SS2>>NOR2x1_In1;
    }
    for (int i=0; i<4; i++) {
        getline(LibInput,S);
    }
    {
        std::stringstream SS(S);
        SS>>S>>S>>S;
        std::stringstream SS2(S);
        SS2>>NOR2x1_In2;
    }
    
    for (int i=0; i<6; i++) 
        getline(LibInput,S);
    
    readTable(NOR2x1_RisePower);
    for (int i=0; i<2; i++) 
        getline(LibInput,S);
    //line37
    readTable(NOR2x1_FallPower);

    for (int i=0; i<4; i++)
        getline(LibInput,S);
    readTable(NOR2x1_CellRise);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NOR2x1_CellFall);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NOR2x1_RiseTransition);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NOR2x1_FallTransition);
    ///////////////////////////////////////////  Cell Invertor   /////////////////////////////
    for (int i=0; i<9; i++)
        getline(LibInput,S);
    
    getline(LibInput,S,';');   getline(LibInput,trash);
    {
        std::stringstream SS(S);
        SS>>S>>S>>S;
        std::stringstream SS2(S);
        SS2>>INV1x1_In1;
    }

    for (int i=0; i<6; i++)
        getline(LibInput,S);
    readTable(INV1x1_RisePower);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(INV1x1_FallPower);

    for (int i=0; i<4; i++)
        getline(LibInput,S);
    readTable(INV1x1_CellRise);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(INV1x1_CellFall);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(INV1x1_RiseTransition);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(INV1x1_FallTransition);

    //////////////////////           cell NAND            ////////////////////
    for (int i=0; i<9; i++)
        getline(LibInput,S);
    getline(LibInput,S,';');
    {
        std::stringstream SS(S);
        SS>>S>>S>>S;
        std::stringstream SS2(S);
        SS2>>NAND2x1_In1;
    }
    
    for (int i=0; i<4; i++)
        getline(LibInput,S);
    getline(LibInput,S,';'); 
    {
        std::stringstream SS(S);
        SS>>S>>S>>S;
        std::stringstream SS2(S);
        SS2>>NAND2x1_In2;
    }
    for (int i=0; i<3; i++)
        getline(LibInput,S);
    getline(LibInput,S,';');
    {
        std::stringstream SS(S);
        SS>>S>>S>>S;
        std::stringstream SS2(S);
        SS2>>NAND2x1_Out1;
    }

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NAND2x1_RisePower);
    
    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NAND2x1_FallPower);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NAND2x1_CellRise);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NAND2x1_CellFall);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NAND2x1_RiseTransition);

    for (int i=0; i<2; i++)
        getline(LibInput,S);
    readTable(NAND2x1_FallTransition);
}

void Parser::readTable(std::vector<std::vector<double>>& Table) {
    double value;
    std::string S, trash;
    std::stringstream SS;
    for (int i=0; i<7; i++) {
        getline(LibInput,S,'"');       getline(LibInput,S,'"');       getline(LibInput,trash);
        std::stringstream SS(S);
        for (int j=0; j<7; j++) {
            getline(SS,S,',');
            std::stringstream SS2(S);
            SS2>>value;
            // value *= 1e6;
            Table[i].push_back(value);
        }
    }
}

void Parser::readFile(const std::string LibInputFileName, const std::string vInputFileName) {
    vFileName = vInputFileName;
    libFileName = LibInputFileName;
    LibInput.open(LibInputFileName);
    if(!LibInput) {    //test if file opened 
        std::cerr << "Can't open "<<LibInputFileName<<"!\n";
        exit(1);     //if unusual, close it 
    }
    vFileName = vInputFileName;
    vInput.open(vInputFileName);
    if(!vInput) {    //test if file opened 
        std::cerr << "Can't open "<<vInputFileName<<"!\n";
        exit(1);     //if unusual, close it 
    }
    readLib();
    readV();
    calCapacity();
    UpdateAdjacency();
    // printV();
    TopologicalSort();
}

void Parser::printIndex() {

    std::cout<<"index1:\n";
    for (auto it1=index1.begin(); it1!=index1.end(); it1++) {
        std::cout<<*it1<<" ";
    }
    std::cout<<"\nindex2\n";
    for (auto it2=index2.begin(); it2!=index2.end(); it2++) {
        std::cout<<*it2<<" ";
    }
}

void Parser::printV() {
    for (int i=0; i<VertexVector.size(); i++) {
        std::cout<<"Vertex "<<vertexName[i]<<"\nGate type: "<<VertexVector[i].gateName<<"\nGate Delay: "<<VertexVector[i].gateDelay<<"\nInput Number: "<<VertexVector[i].inputNum;
        std::cout<<"\noutputValue: "<<VertexVector[i].outputValue<<"\ninputCapacity1: "<<VertexVector[i].inputCapacity1<<"\ninputCapacity2: "
        <<VertexVector[i].inputCapacity2<<"\nOutput Capacitance: "<<VertexVector[i].outputCapacity<<"\ninputTransTime: "
        <<VertexVector[i].inputTransTime<<"\noutputTransTime: "<<VertexVector[i].outputTransTime<<"\n";
        std::cout<<"\nOut AdjacencyList\n";
        for (int j=0; j<VertexVector[i].OutAdjacencyList.size(); j++) {
            std::cout<<vertexName[VertexVector[i].OutAdjacencyList[j]]<<" ";
        }
        std::cout<<"\nInAdjacencyList\n";
        for (int j=0; j<VertexVector[i].InAdjacencyList.size(); j++) {
            std::cout<<vertexName[VertexVector[i].InAdjacencyList[j]]<<" ";
        }
        std::cout<<"\nInput Net\n";
        for (int j=0; j<VertexVector[i].inputNet.size(); j++) {
            std::cout<<netName[VertexVector[i].inputNet[j]]<<" ";
        }
        std::cout<<"\nOutput Net\n";
        for (int j=0; j<VertexVector[i].outputNet.size(); j++) {
            std::cout<<netName[VertexVector[i].outputNet[j]]<<" ";
        }std::cout<<"\n";
    }
}

void Parser::printTable (std::vector<std::vector<double>>& Table) {
    std::cout<<"Print Table\n";
    for (auto it1=Table.begin(); it1!=Table.end(); it1++) {
        for (auto it2=it1->begin(); it2!=it1->end(); it2++) {
            std::cout<<setiosflags(std::ios::left)<<std::setw(7);
            std::cout<<*it2<<" ";
        }
        std::cout<<"\n";
    }
}

void Parser::printNet() {
    for (int i=0; i<NetVector.size(); i++) {
        std::cout<<"\nnet "<<netName[i]<<"\nIn Gate\n";
        for (auto it=NetVector[i].InGate.begin(); it!=NetVector[i].InGate.end(); it++) {
            std::cout<<vertexName[*it]<<" ";
        }std::cout<<"\nOut Gate\n";
        for (auto it=NetVector[i].OutGate.begin(); it!=NetVector[i].OutGate.end(); it++) {
            std::cout<<vertexName[*it]<<" ";
        }std::cout<<"\n";
    }
}

void Parser::printLongestPath() {
    double Max(0);
    int index(0);
    std::stack<std::string> path;
    for (int i=0; i<outputGate.size(); i++) {
        if (VertexVector[outputGate[i]].sensiDelay > Max) {
            Max = VertexVector[outputGate[i]].sensiDelay;
            index = outputGate[i];
        }
    }
    output<<"Longest delay = "<<VertexVector[index].sensiDelay<<", the path is:\n";
    while (!VertexVector[index].inputNet.empty()) {
        path.push(netName[VertexVector[index].inputNet[VertexVector[index].controling]]);
        index = VertexVector[index].InAdjacencyList[VertexVector[index].controling];
    }
    std::string net;
    net = path.top();   path.pop();
    output<<net;
    while(!path.empty()) {
        net = path.top();   path.pop();
        output<<" -> "<<net;
    }output<<"\n\n";
}

void Parser::printOrder() {
    std::cout<<"Print Topological Order:\n";
    for (auto it1=noInputGate.begin(); it1!=noInputGate.end(); it1++) {
        for (auto it2=it1->begin(); it2!=it1->end(); it2++) {
            std::cout<<vertexName[*it2]<<" ";
        }std::cout<<"\n";
    }
}

void Parser::printNormalForm() {
    for (int i=0; i<VertexVector.size(); i++) {
        if (VertexVector[i].sink || VertexVector[i].source)
            continue;
        output<<vertexName[i]<<" "<<VertexVector[i].outputValue<<" "<<VertexVector[i].gateDelay<<" "<<VertexVector[i].outputTransTime<<"\n";
    }output<<"\n";
}

void Parser::openOutput () {
    auto pos = vFileName.find_last_of("/");
    if (pos == std::string::npos) {
        outputFileName = "309551055_" + vFileName.substr(0, vFileName.size()-2) + ".txt";
    }
    else {
        outputFileName = "309551055_" + vFileName.substr(pos+1, vFileName.size()-3-pos) + ".txt";
    }

    output.open(outputFileName);
    if(!output) {    //test if file opened 
        std::cerr << "Can't open "<<outputFileName<<"!\n";
        exit(1);     //if unusual, close it 
    }
}
#endif