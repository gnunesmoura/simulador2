#include <iostream>
#include <stdio.h>
#include <string>
#include <dirent.h>

#include "init/test/tests.hpp"
#include "init/evaluation/result.hpp"

using namespace std;

int main (int argc, char* argv[]) {
    cout << "\nstarting\n\n";
    vector<string> instancias;

    instancias.reserve(200);
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("instancias/loc/")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            // printf ("%s\n", ent->d_name);
            string d_name(ent->d_name);
            if(d_name.size() > 3) {
                d_name.erase(d_name.find("_loc.txt"));
                instancias.push_back(d_name);
            }
        }
    
    closedir (dir);
    
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    sort(instancias.begin(), instancias.end());
    string arg("-");
    if(argc >= 2) arg = argv[1];

    sim::Result r (arg);
    std::cout << "\tdesvMed\t\tdesvMax\t\tdesvQuad\trmsd\t\tpar\n";
    if(argc < 2) {
        for_each(instancias.begin(), instancias.end(), [&](string inst){
            cout << run(inst) << '\n';
        });
    } else if (argc == 3) {
        for_each(instancias.begin(), instancias.end(), [&](string inst){
            if( inst.substr(0, arg.size()) == arg) run_geogebra(inst, 0.01);
        });    
    } else {
        for_each(instancias.begin(), instancias.end(), [&](string inst){
            if( inst.substr(0, arg.size()) == arg) cout << run(inst) << '\n';
        });
    }
    
    return 0;
}
// s.solve ();

    