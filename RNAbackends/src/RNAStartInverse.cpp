/*
 * File:   RNAStartInverse.cpp
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

#include <mili/mili.h>
#include "RNAStartInverse.h"

RNAStartInverse::RNAStartInverse(const SecStructure& structure, Similitude sd, Distance hd, CombinationAttempts ca) :
        rstart(), found(), combination_attempts(ca), combinator(new SeqIndexesCombinator(structure.size(), hd)),
        positions(), start(), structure(structure), max_structure_distance(sd), max_sequence_distance(hd)
        
{}

RNAStartInverse::~RNAStartInverse()
{
    delete combinator;
}

void RNAStartInverse::fold_inverse(NucSequence& sequence) throw(RNABackendException)
{
    string seq;
    Distance hd;
    Similitude sd;

    CombinationAttempts i = combination_attempts;
    bool c;
    do
    {
        --i;        
        do
        {
            execute(seq, hd, sd);
        }
        while (sd > max_structure_distance);

        //If the sequence found was already returned and we reach the number
        //of attempts for the current combination of free positions in 'start',
        //we move to the next combination, change the 'start' and re-start the
        //number of attempts.
        c = contains(found, seq);
        if (c && i==0)
        {
            combinator->next(positions);
            change_start();
            i = combination_attempts;
        }
    }
    while (c);

    //Adds the sequence found to the set.
    insert_into(found, seq);
    sequence = seq;
}

void RNAStartInverse::set_start(const NucSequence& sequence)
{
    if (sequence.length() < max_sequence_distance)
        throw RNABackendException("Start sequence must have at least 'max_sequence_distance' length");
    
    //clear any previous start and found set.
    start.clear();
    found.clear();
    //Sets the start in lowercase. We need this to avoid that RNAinverse
    //make changes everywhere.
    for (size_t i=0; i<sequence.length(); ++i)
    {
        start += tolower(to_str(sequence[i])[0]);
    }
    //Adds the start to the set of found sequences.
    insert_into(found, start);

    //rembember the original start.
    rstart = start;

    //Begin the combinator and set the first free positions.
    combinator->begin();
    combinator->next(positions);
    change_start();
}

void RNAStartInverse::change_start()
{
    //Gets the original start
    start = rstart;
    CAutonomousIterator<SeqIndexesCombination> it(positions);
    while(!it.end())
    {
        //This let to search for possible changes in each position.
        start[*it] = WILDCARD;
        ++it;
    }
}
