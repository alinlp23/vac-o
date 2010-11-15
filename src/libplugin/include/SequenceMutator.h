/*
 * File:   SequenceMutator.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 6:54 PM
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

#ifndef _SEQUENCEMUTATOR_H
#define	_SEQUENCEMUTATOR_H

#include "exceptions.h"
#include "types.h"
#include "Combinator.h"
#include "rna_backends_types.h"
/**
 * Iterator over sequence mutations.
 * From N simultaneos mutations to single mutations.
 */
class SequenceMutator
{
    NucSequence sequence;
    NucSequence mutated;
    const size_t seq_length;
    NMutations mutations;
    const NMutations rmutations;
    
    SeqIndexesCombinator* const combinator;
    SeqIndexesCombination positions;

    /**
     * Set the iterator at the begining for the current
     * positions being mutated.
     */
    void reset();
    /**
     * Update the combinator iterator for the current
     * number of simultaneos mutations
     */
    void update_combinator();
    /**
     * Gets the next mutations for the current number
     * of mutations and positions.
     * @param seq the sequence to write to the mutation.
     * @return If there are more mutations pending.
     */
    bool next_mutation(NucSequence&);

    /**
     * Initialize the mutator
     */
    void begin();
public:
    /**
     * Constructor
     * @param sequence the initial sequence.
     * @param max_mutations the maxium number of simultaneos mutations
     */
    SequenceMutator(const NucSequence&, NMutations);

    /**
     * Constructor
     * @param length the sequence length
     * @param max_mutations the maxium number of simultaneos mutations
     */
    SequenceMutator(size_t, NMutations);
    /**
     * Gets the next mutation.
     * @param seq the sequence to write to the mutation.
     * @return If there are more mutations pending.
     */
    bool next(NucSequence&);
    /**
     * Re-initialize the mutator using the given sequence
     * @param seq the sequence.
     */
    void begin(const NucSequence&) throw(PluginException);
    
    ~SequenceMutator();    
};

#endif	/* _SEQUENCEMUTATOR_H */

