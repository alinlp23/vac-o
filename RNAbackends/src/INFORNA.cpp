/*
 * File:   INFORNA.cpp
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 10, 2010, 4:26 PM
 *
 * Copyright (C) 2010  Santiago Videla, FuDePAN
 *
 * This file is part of vac-o
 *
 * vac-o is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * vac-o is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vac-o.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <sstream>
#include <string>
#include <mili/mili.h>

#include "INFORNA.h"
#include "IStartProvider.h"
#include "RNABackendsConfig.h"

using std::string;
using std::stringstream;

const FilePath INFORNA::OUT = "inverse.out";
const FileLineNo INFORNA::LINE_NO = 13;

INFORNA::INFORNA(const SecStructure& structure, Similitude sd, Distance hd, CombinationAttempts ca) :
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
    ss << INFORNA_PROG << " '" << structure.to_str() << "'"
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
        read_value(line, from, to - from, seq);

        for (size_t i = 0; i < seq.size(); ++i)
            seq[i] = tolower(seq[i]);

        return to;
    }
    catch (const StringNotFound& e)
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
        read_value(line, from, to - from, hd);
        return to;
    }
    catch (const StringNotFound& e)
    {
        throw RNABackendException("Could not read hamming distance");
    }
}

size_t INFORNA::read_structure_distance(FileLine& line, size_t offset, Similitude& sd) const throw(RNABackendException)
{
    try
    {
        const size_t from = ensure_found(line.find_first_of("d", offset)) + 3;
        const size_t to = line.size();
        read_value(line, from, to - from, sd);
        return to;
    }
    catch (const StringNotFound& e)
    {
        sd = 0;
        return line.size();
    }
}
