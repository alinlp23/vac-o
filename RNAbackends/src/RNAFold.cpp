#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <mili/mili.h>

using std::string;
using std::ofstream;
using std::ifstream;

#include "RNAFold.h"

Fe RNAFold::fold(const NucSequence& sequence, SecStructure& structure) const throw(RNABackendException)
{
    string cmd = "RNAfold -noPS < fold.in > fold.out";
    string sseq;
    ofstream out("fold.in");

    for (size_t i=0; i<sequence.length(); ++i)
    {
        sseq += to_str(sequence[i])[0];
    }

    out << sseq << "\n";
    out.close();

    int status = system(cmd.c_str());
    if (status)
        throw RNABackendException("An error ocurred trying to execute: "+cmd);

    ifstream in("fold.out");
    /* fold.out look like this:
     * CGCAGGGAUCGCAGGUACCCCGCAGGCGCAGAUACCCUA
     * ...(((((((....(..((.....))..).))).)))). (-10.80)
    */
    string aux;
    //ignore first line (the sequence folded)
    getline(in, aux);

    getline(in, aux);
    structure = aux.substr(0, sequence.length());

    Fe energy;
    int from = aux.find_first_not_of(" ", sequence.length()) + 1;
    int to = aux.find_first_of(" ", from) - 1;
    from_string<Fe>(aux.substr(from, to-from), energy);

    return energy;
}