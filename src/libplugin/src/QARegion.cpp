/*
 * File:   QARegion.cpp
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

#include <iostream>
#include "vaco-libplugin/QARegion.h"
#include "vaco-libplugin/IQAMutator.h"
#include "vaco-libplugin/IQAValidator.h"

using std::cout;
using std::endl;

QARegion::QARegion(SeqIndex s, SeqIndex e, Depth d, IQAMutator* m, const IQAValidator* v) :
    start(s), end(e), depth(d), mutator(m), validator(v)
{}

bool QARegion::validate(const NucSequence& seq) const
{
    Depth d = 0;
    queue<NucSequence> mutants;

    //Extract the region from the complete sequence
    NucSequence region;
    string str_r;
    for (SeqIndex i = start; i < end; ++i)
        str_r += to_str(seq[i]);
    region = str_r;

    insert_into(mutants, region);
    bool pass = validator->validate(seq);

    while (pass && d < depth && !mutants.empty())
    {
        pass = validate_level(seq, mutants);
        ++d;
    }
    return pass;
}

bool QARegion::validate_level(const NucSequence& seq, queue<NucSequence>& mutants) const
{
    bool pass(true);
    size_t mlevel = mutants.size();
    while (pass && mlevel > 0)
    {
        const NucSequence current = mutants.front();
        mutants.pop();
        pass = validate_mutants(seq, current, mutants);
        --mlevel;
    }
    return pass;
}

bool QARegion::validate_mutants(const NucSequence& seq, const NucSequence& region, queue<NucSequence>& mutants) const
{
    bool pass(true);

    mutator->set_base_sequence(region);
    NucSequence mutant;
    NucSequence complete_mutant = seq;
    while (pass && mutator->next(mutant))
    {
        //restore the complete sequence in order to validate it.
        for (SeqIndex i = 0; i < mutant.length(); ++i)
            complete_mutant[start + i] = mutant[i];

        pass = validator->validate(complete_mutant);
        if (pass)
            insert_into(mutants, mutant);
    }
    return pass;
}
