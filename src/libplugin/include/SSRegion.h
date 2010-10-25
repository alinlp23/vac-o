/*
 * File:   SSRegion.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:16 PM
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

#ifndef _SSREGION_H
#define	_SSREGION_H

#include "CombinatoryRegion.h"
#include "IStartProvider.h"

class IFold;
class IFoldInverse;
class IStructureCmp;
class ISequenceCmp;

class SSRegion : public CombinatoryRegion, public IStartProvider
{
    SecStructure wt_structure;
    SecStructure vaccine_structure;
    NMutations max_mutations;
    Similitude max_similitude;
    Distance min_distance;
    const NucSequencesCt wildtype_cache;

    /*libRNA backends*/
    const IFold* const fold_backend;
    IFoldInverse* const inverse_backend;
    const IStructureCmp* const struct_cmp_backend;
    const ISequenceCmp* const seq_cmp_backend;

    virtual Score evaluate(const NucSequence&) const;
    virtual Score generate(NucSequence&, NucSequence&);
    virtual void set_base_sequence(const NucSequence& sequence);

    // Implements IStartProvider
    virtual void get_partial_start(IFoldInverse* const);
    virtual void get_complete_start(IFoldInverse* const);
public:
    SSRegion(SeqIndex, SeqIndex, const SecStructure&, const SecStructure&,
             NMutations, Similitude, Distance, const NucSequencesCt&,
             const IFold* const, IFoldInverse* const, const IStructureCmp* const,
             const ISequenceCmp* const);

    SSRegion(const SSRegion&);
    SSRegion& operator=(const SSRegion&);
};

#endif	/* _SSREGION_H */

