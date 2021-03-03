// #include <bits/stdc++.h>
// #include "TableElement.h"
// #include "parser.h"
// using namespace std;
// /////////////////////////////Constructor//////////////////////////////
// Parser::Parser(std::string s):InFileName(s) {
//     }

// //////////////////////////////Read File///////////////////////////////
// void Parser::readInputFile(const std::string fileName) {
//     bitset<10> dcterm, minterm;
//     std::string trash, S;
//     vector<TableElement> onSet, dcSet;
//     std::cout<<"file name: "<<fileName<<"/"<<"\n";
//     InFileName = fileName;
//     input.open(InFileName);
//     if(!input) {    //test if file opened 
//         std::cerr << "Can't open "<<fileName<<"!\n";
//         exit(1);     //if unusual, close it 
//     }

//     getline(input,S); 
//     {
//         std::stringstream SS(S);
//         SS>>trash>>var;
//     }
//     std::cout<<"var: "<<var<<"\n";
//     getline(input,S);
//     getline(input,S);
//     {
//         std::stringstream SS(S);
//         while (SS>>minterm){
//             std::cout<<minterm<<"\n";
//             TableElement TE;
//             TE.value = minterm;
//             onSet.push_back(TE);
//         }
//     }
//     std::cout<<"On Set:\n";
//     for (int i=0; i<onSet.size(); i++) {
//         std::cout<<onSet[i].value<<" ";
//     }
//     getline(input,S);
//     getline(input,S);
//     std::stringstream SS(S);
//     while (SS>>dcterm) {
//         TableElement TE;
//         TE.value = dcterm;
//         dcSet.push_back(TE);
//     }
//     std::cout<<"\ndc set\n";
//     for (int i=0; i<dcSet.size(); i++) {
//         std::cout<<dcSet[i].value<<" ";
//     }
//     std::cout<<"\n";
//     return;
// }

// void Parser::readInputFile() {
//     bitset<10> dcterm, minterm;
//     std::string trash, S;
//     vector<TableElement> onSet, dcSet;
//     std::cout<<"file name: "<<fileName<<"/"<<"\n";
//     InFileName = fileName;
//     input.open(InFileName);
//     if(!input) {    //test if file opened 
//         std::cerr << "Can't open "<<fileName<<"!\n";
//         exit(1);     //if unusual, close it 
//     }

//     getline(input,S); 
//     {
//         std::stringstream SS(S);
//         SS>>trash>>var;
//     }
//     std::cout<<"var: "<<var<<"\n";
//     getline(input,S);
//     getline(input,S);
//     {
//         std::stringstream SS(S);
//         while (SS>>minterm){
//             std::cout<<minterm<<"\n";
//             TableElement TE;
//             TE.value = minterm;
//             onSet.push_back(TE);
//         }
//     }
//     std::cout<<"On Set:\n";
//     for (int i=0; i<onSet.size(); i++) {
//         std::cout<<onSet[i].value<<" ";
//     }
//     getline(input,S);
//     getline(input,S);
//     std::stringstream SS(S);
//     while (SS>>dcterm) {
//         TableElement TE;
//         TE.value = dcterm;
//         dcSet.push_back(TE);
//     }
//     std::cout<<"\ndc set\n";
//     for (int i=0; i<dcSet.size(); i++) {
//         std::cout<<dcSet[i].value<<" ";
//     }
//     std::cout<<"\n";
//     return;
// }
// ///////////////////////////////Output File/////////////////////////////
// void Parser::writeOutputFile(const std::string fileName) {
//     OutFileName = fileName;
//     output.open(OutFileName);

// }