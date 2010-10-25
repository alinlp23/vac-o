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

#include "RNAinverse.h"
#include "IStartProvider.h"

RNAinverse::RNAinverse(const SecStructure& structure, Similitude sd, Distance hd, Attempts ca) :
        RNAStartInverse(structure, sd, hd, ca), cmd()
{
    stringstream ss;
    int repeat = max_structure_distance == 0 ? -1 : 1;
    ss << "RNAinverse -R " << repeat << " -a ATGC < inverse.in > inverse.out";
    cmd = ss.str();
}

void RNAinverse::query_start(IStartProvider* provider) throw(RNABackendException)
{
    provider->get_partial_start(this);
    if (start.size() != structure.size())
        throw RNABackendException("Partial start and target structure must have the same length");
}

void RNAinverse::execute(string& seq, Distance& hd, Similitude& sd) throw(RNABackendException)
{
    ofstream out("inverse.in");
    out << structure << "\n";
    out << start << "\n";

    out.close();

    int status = system(cmd.c_str());
    if (status)
        throw RNABackendException("An error ocurred trying to execute: "+cmd);

    ifstream in("inverse.out");

    string aux;
    getline(in, aux);
    /* aux looks like this
     * accagggATCgcaggtaccccgcaGGcgcagAacccta   5 2   d= 2
     *
     * where uppercases were set by RNAinverse (dots in our start).
     * 5 it's the hamming distance from the random generated start and the
     * sequence found. And 2 it's the structure distance to the target structure.
     * If max_structure_distance=0 then, this will be also equal to 0.
     */

    //sequence found
    seq = aux.substr(0, start.size());
    for (size_t i=0; i<start.size(); ++i)
    {
        //all to lower because we will need to compare this sequence with the
        //sequences in found set.
        seq[i] = tolower(aux[i]);
    }

    //hamming distance from the start used
    int from = aux.find_first_not_of(" ", start.size());
    int to = aux.find_first_of(" ", from);
    from_string<Distance>(aux.substr(from, to-from), hd);

    //structure distance from the sequence found to the target structure.
    from = aux.find_first_not_of(" ", to);
    to = aux.find_first_of(" ", from);
    from_string<Similitude>(aux.substr(from, to-from), sd);
}