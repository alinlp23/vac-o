/*
 * File:   RandomMutator.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 9, 2010, 4:19 PM
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

#ifndef _RANDOMMUTATOR_H
#define _RANDOMMUTATOR_H

#include "vaco-commons/types.h"
#include "vaco-libplugin/IQAMutator.h"

typedef float MutationMatrix[MATRIX_SIZE][MATRIX_SIZE];

class IMutationMatrixProvider
{
public:
    virtual void get_mutation_matrix(MutationMatrix& m) const = 0;
    virtual ~IMutationMatrixProvider() {}

};

/**
 * Iterates over a number of 'mutants' mutations
 * where each mutation has up to 'mutations' random
 * mutations using the mutation matrix.
 */
class RandomMutator : public IQAMutator
{
    NucSequence sequence;
    const NMutations mutations;
    const NMutations mutants;
    NMutations counter;
    MutationMatrix matrix;

    mili::Randomizer<float> rnd;

    virtual bool next(NucSequence&);
    virtual void set_base_sequence(const NucSequence&);
public:
    /**
     * Constructor using default mutation matrix
     * @param mutations the number of random mutations.
     * @param mutants the number of mutants being generated.
     */
    RandomMutator(NMutations, NMutations);

    /**
     * Constructor asking for a custom mutation matrix
     * @param mutations the number of random mutations to made
     * @param mutants the number of mutants being generated.
     * @param provider the mutation matrix provider
     */
    RandomMutator(NMutations, NMutations, const IMutationMatrixProvider* const);

    virtual ~RandomMutator()
    {}
};

#endif  /* _RANDOMMUTATOR_H */

