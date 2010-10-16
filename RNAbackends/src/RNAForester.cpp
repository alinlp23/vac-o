#include <fstream>
#include <string>
#include <cstdlib>
#include <mili/mili.h>
#include "RNAForester.h"

using std::string;
using std::ofstream;
using std::ifstream;

Similitude RNAForester::compare(const SecStructure& struct1,
                                const SecStructure& struct2) const throw(RNABackendException)
{
    ofstream out(".forester.in");
    out << struct1 << "\n"
    << struct2 << "\n";

    out.close();

    string cmd = "RNAforester -r --score -f .forester.in > .forester.out";
    int status = system(cmd.c_str());
    if (status)
        throw RNABackendException("An error ocurred trying to execute: "+cmd);

    ifstream in(".forester.out");
    Similitude s;
    string aux;
    /*ignore first line (global optimal score)*/
    getline(in, aux);
    /*gets second line (relative score)*/
    getline(in, aux);
    from_string<Similitude>(aux, s);

    return s;
}
