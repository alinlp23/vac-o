/*
 * File:   RandomMutator.cpp
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
#include "fideo/rna_backends_types.h"
#include "vaco-libplugin/RandomMutator.h"

inline void initialize_mutation_matrix(MutationMatrix& matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE; ++i)
    {
        for (size_t j = 0; j < MATRIX_SIZE; ++j)
            matrix[i][j] = i == j ? 0.f : 1.f / 3.f;
    }
}

RandomMutator::RandomMutator(NMutations mutations, NMutations mutants) :
    sequence(), mutations(mutations), mutants(mutants), counter(0), matrix(), rnd(0.f, 1.f)
{
    initialize_mutation_matrix(matrix);
}

RandomMutator::RandomMutator(NMutations mutations, NMutations mutants, const IMutationMatrixProvider* provider) :
    sequence(), mutations(mutations), mutants(mutants), counter(0), matrix(), rnd(0, 1)
{
    initialize_mutation_matrix(matrix);
    provider->get_mutation_matrix(matrix);
}

bool RandomMutator::next(NucSequence& seq)
{
    ++counter;
    bool more(counter <= mutants);

    if (more)
    {
        seq = sequence;
        NMutations i = 0;
        const size_t length = sequence.length() - 1;
        while (i < mutations)
        {
            const SeqIndex pos = SeqIndex(rnd.get() * length);
            float prob;

            do
            {
                /*
                 * This is useful to disable mutation between some bases.
                 * To disable i->j mutations, set matrix[i][j] = 0.f
                 *
                 * If we don't ensure prob != 0 this is not possible. Anyways
                 * the probability of getting exactly 0 (or any number) from a
                 * random generator it's also 0.
                */
                prob = rnd.get();
            }
            while (prob == 0.f);

            Nucleotide b = Nucleotide(0);
            float acc = matrix[seq[pos]][b];
            while (acc < prob)
            {
                b = Nucleotide((b + 1) % 4);
                acc += matrix[seq[pos]][b];
            }
            seq[pos] = b;

            ++i;
        }
    }
    return more;
}

void RandomMutator::set_base_sequence(const NucSequence& seq)
{
    sequence = seq;
    counter = 0;
}
