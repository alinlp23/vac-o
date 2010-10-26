#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <mili/mili.h>

using std::string;
using std::ofstream;
using std::ifstream;
using std::stringstream;

#include "INFORNA.h"
#include "IStartProvider.h"

INFORNA::INFORNA(const SecStructure& structure, Similitude sd, Distance hd, Attempts ca) :
        RNAStartInverse(structure, sd, hd, ca)
{}

void INFORNA::query_start(IStartProvider* provider) throw(RNABackendException)
{
    provider->get_partial_start(this);
    if (start.size() != structure.size())
        throw RNABackendException("Partial start and target structure must have the same length");
}

void INFORNA::execute(string& seq, Distance& hd, Similitude& sd) throw(RNABackendException)
{
    stringstream ss;
    int repeat = max_structure_distance == 0 ? -1 : 1;
    ss << "INFO-RNA-2.1 '" << structure << "'"
       << " -c '" << start << "'"
       << " -R " << repeat << " > inverse.out";

    string cmd = ss.str();
    int status = system(cmd.c_str());
    if (status)
        throw RNABackendException("An error ocurred trying to execute: "+cmd);

    ifstream in("inverse.out");
    /* inverse.out looks like this:
     *
     * =========================
     * Initializing Step:
     * =========================
     * Wanted Structure    : (..((.....))..)
     * Sequence Constraints: NNNNNNNNNUGCCGC
     * Allowed Mismatches  : 000000000000000
     * Designed Sequence   : GUAGCUUUAUGCCGC
     * designed randomly   : 0
     *
     * =========================
     * Local Search Results:
     * =========================
     * MFE:    GUAGCUUUAUGCCGC    0  (-1.70)   d= 1
     * number of mismatches: 0
     *
     */
    string aux;
    //ignore the first 12 lines
    for (size_t i=0; i<13; ++i)
        getline(in, aux);

    getline(in, aux);
    
    //sequence found
    size_t from = aux.find_first_of(" ", 0);
    size_t to = aux.find_first_not_of(" ", from);
    seq = aux.substr(to, start.size());    
    for (size_t i=0; i<start.size(); ++i)
    {
        //all to lower because we will need to compare this sequence with the
        //sequences in found set.
        seq[i] = tolower(seq[i]);
    }

    //hamming distance from the start used
    from = aux.find_first_not_of(" ", start.size());
    to = aux.find_first_of(" ", from);
    from_string<Distance>(aux.substr(from, to-from), hd);

    //structure distance from the sequence found to the target structure.
    from = aux.find_first_of("d= ", to);    
    if (from != to)
    {
        to = aux.find_first_of(" ", from);
        from_string<Similitude>(aux.substr(from, to-from), sd);
    }
    else
        sd = 0;    
}
