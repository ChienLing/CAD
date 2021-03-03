#include <bits/stdc++.h>
#include "Parser.h"
using namespace std;
int main (int argc, char **argv) {
    Parser* parser = new Parser;
    string lib, V, pat;
    if (argc < 6){
        cout<<"usage: % a.out netlist_file -p input.pat -l testlib.lib\n";
        return 0;
    }
    V = string(argv[1]);
    if (string(argv[2]) == "-p"){
        pat = string(argv[3]);
        lib = string(argv[5]);
    }
    else if (string(argv[2]) == "-l") {
        lib = string(argv[3]);
        pat = string(argv[5]);
    }

    else
    {
        cout<<"usage: % a.out netlist_file -p input.pat -l testlib.lib\n";
        return 0;
    }
    
    
    parser->readFile(lib, V);
    parser->readInput(pat);
    return 0;
}