/*
 * File:   RNAinverse.cpp
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
#include "RNAinverse.h"
#include "IStartProvider.h"
using std::stringstream;

const FilePath RNAinverse::IN = "inverse.in";
const FilePath RNAinverse::OUT = "inverse.out";
const FileLineNo RNAinverse::LINE_NO = 0;

RNAinverse::RNAinverse(const SecStructure& structure, Similitude sd, Distance hd, CombinationAttempts ca) :
        RNAStartInverse(structure, sd, hd, ca)
{}

void RNAinverse::query_start(IStartProvider* provider) throw(RNABackendException)
{
    provider->get_partial_start(this);
    if (start.size() != structure.size())
        throw RNABackendException("Partial start and target structure must have the same length");
}

void RNAinverse::execute(string& seq, Distance& hd, Similitude& sd) throw(RNABackendException)
{          
    FileLinesCt lines;
    insert_into(lines, structure.to_str());
    insert_into(lines, start);
    write(IN, lines);

    stringstream ss;
    int repeat = max_structure_distance == 0 ? -1 : 1;
    ss << "RNAinverse -R " << repeat << " -a ATGC < " << IN << " > " << OUT;
    const string CMD = ss.str();
    
    exec(CMD);

    FileLine aux;
    read_line(OUT, LINE_NO, aux);
    /* aux looks like this
     * accagggATCgcaggtaccccgcaGGcgcagAacccta   5 2   d= 2
     *
     * where uppercases were set by RNAinverse (dots in our start).
     * 5 it's the hamming distance from the random generated start and the
     * sequence found. And 2 it's the structure distance to the target structure.
     * If max_structure_distance=0 then, this will be also equal to 0.
     */
    read_value(aux, 0, start.size(), seq);    
    for (size_t i=0; i<start.size(); ++i)            
        seq[i] = tolower(seq[i]);

    //hamming distance from the start used
    const size_t sd_offset = read_hamming_distance(aux, start.size(), hd);
    //structure distance from the sequence found to the target structure.
    read_structure_distance(aux, sd_offset, sd);
}

size_t RNAinverse::read_hamming_distance(FileLine& line, size_t offset, Distance& hd) const throw(RNABackendException)
{    
    try
    {
        const size_t from = ensure_found(line.find_first_not_of(" ", offset));
        const size_t to = ensure_found(line.find_first_of(" ", from));
        read_value(line, from, to-from, hd);
        return to;
    }
    catch (const StringNotFound& e)
    {
        throw RNABackendException("Could not read hamming distance");
    }    
}

size_t RNAinverse::read_structure_distance(FileLine& line, size_t offset, Similitude& sd) const throw(RNABackendException)
{    
    try
    {
        const size_t from = ensure_found(line.find_first_not_of(" ", offset));
        const size_t to = ensure_found(line.find_first_of(" ", from), line.size());
        read_value(line, from, to-from, sd);
        return to;
    }
    catch (const StringNotFound& e)
    {
        throw RNABackendException("Could not read structure distance");
    }    
}