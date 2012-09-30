/*
 * File:   SequenceMutator.cpp
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

#include "vaco-libplugin/SequenceMutator.h"

SequenceMutator::SequenceMutator(const NucSequence& seq, NMutations max) :
    sequence(seq), mutated(seq), seq_length(seq.length()), mutations(max),
    rmutations(max), combinator(new SeqIndexesCombinator(seq.length(), max)),
    positions()
{
    begin();
}

SequenceMutator::SequenceMutator(size_t length, NMutations max) :
    sequence(), mutated(), seq_length(length), mutations(max), rmutations(max),
    combinator(new SeqIndexesCombinator(length, max)), positions()
{}

SequenceMutator::~SequenceMutator()
{
    delete combinator;
}

void SequenceMutator::begin()
{
    combinator->begin();
    combinator->next(positions);
    reset();
}

void SequenceMutator::begin(const NucSequence& seq) throw(PluginException)
{
    if (seq.length() != seq_length)
        throw PluginException(" SequenceMutator: sequence length must be equal to the length given at initialization");

    mutations = rmutations;
    combinator->update(mutations);
    sequence = seq;
    mutated = seq;
    begin();
}

void SequenceMutator::update_combinator()
{
    combinator->update(mutations);
    combinator->next(positions);
}

void SequenceMutator::reset()
{
    for (size_t i = 0; i < positions.size(); ++i)
    {
        SeqIndex pos = positions[i];
        mutated[pos] = Nucleotide((mutated[pos] + 1) % 4);
    }
}

bool SequenceMutator::next(NucSequence& seq)
{
    bool more;
    if (mutations > 0)
    {
        more = next_mutation(seq);
        if (!more)
        {
            more = true;
            if (!combinator->next(positions))
            {
                --mutations;
                if (mutations > 0)
                    update_combinator();
            }
            mutated = sequence;
            reset();
        }
    }
    else
        more = false;
    return more;
}

bool SequenceMutator::next_mutation(NucSequence& seq)
{
    seq = mutated;

    SeqIndex pos = positions[positions.size() - 1];
    mutated[pos] = Nucleotide((mutated[pos] + 1) % 4);
    if (mutated[pos] == sequence[pos] && mutations > 1)
        reset();

    return mutated[positions[0]] != sequence[positions[0]];
}
