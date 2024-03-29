/*
 * File:   AllMutator.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 9, 2010, 4:06 PM
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

#ifndef _ALLMUTATOR_H
#define _ALLMUTATOR_H

#include "vaco-commons/types.h"
#include "vaco-libplugin/IQAMutator.h"
#include "vaco-libplugin/SequenceMutator.h"

/**
 * Adapts SequenceMutator to IQAMutator
 *
 * Iterates over all possible mutations, from the
 * 'mutations' simultaneos mutations down to
 * every single mutation.
 */
class AllMutator : public IQAMutator
{
    SequenceMutator mutator;
    const NMutations mutations;

    virtual bool next(NucSequence&);
    virtual void set_base_sequence(const NucSequence&);
public:
    /**
     * Constructor
     * @param length the sequence's length
     * @param mutations the maxium number of simultaneos mutations
     */
    AllMutator(size_t, NMutations);
};


#endif  /* _ALLMUTATOR_H */

