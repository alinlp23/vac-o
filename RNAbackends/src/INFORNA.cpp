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

const Path INFORNA::OUT = "inverse.out";
const FileLineNo INFORNA::LINE_NO = 13;


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
       << " -R " << repeat << " > " << OUT;

    string const CMD = ss.str();
    exec(CMD);

    FileLine aux;
    read_line(OUT, LINE_NO, aux);
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
    //sequence found
    const size_t hd_offset = read_sequence(aux, 4, seq);
    //hamming distance from the start used
    const size_t sd_offset = read_hamming_distance(aux, hd_offset, hd);
    //structure distance from the sequence found to the target structure.
    read_structure_distance(aux, sd_offset, sd);
}

size_t INFORNA::read_sequence(FileLine& line, size_t offset, string& seq) const throw(RNABackendException)
{
    try
    {
        const size_t from = ensure_found(line.find_first_not_of(" ", offset));
        const size_t to = ensure_found(line.find_first_of(" ", from));
        read_value(line, from, to-from, seq);

        for (size_t i=0; i<seq.size(); ++i)
            seq[i] = tolower(seq[i]);

        return to;
    }
    catch (StringNotFound e)
    {
        throw RNABackendException("Could not read sequence");
    }
}

size_t INFORNA::read_hamming_distance(FileLine& line, size_t offset, Distance& hd) const throw(RNABackendException)
{
    try
    {
        const size_t from = ensure_found(line.find_first_not_of(" ", offset));
        const size_t to = ensure_found(line.find_first_of(" ", from));
        read_value(line, from, to-from, hd);
        return to;
    }
    catch (StringNotFound e)
    {
        throw RNABackendException("Could not read hamming distance");
    }
}

size_t INFORNA::read_structure_distance(FileLine& line, size_t offset, Similitude& sd) const throw(RNABackendException)
{
    try
    {
        const size_t from = ensure_found(line.find_first_of("d", offset)) + 3;
        const size_t to = ensure_found(line.find_first_of(" ", from));
        read_value(line, from, to-from, sd);
        return to;
    }
    catch (StringNotFound e)
    {
        sd = 0;
        return line.size();
    }
}
