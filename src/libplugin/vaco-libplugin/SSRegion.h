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
#define _SSREGION_H

#include "fideo/RnaBackendsTypes.h"
#include "fideo/IFold.h"
#include "fideo/IStartProvider.h"
#include "fideo/IStructureCmp.h"
#include "vaco-libplugin/CombinatoryRegion.h"

using biopp::SecStructure;

class IFoldInverse;
class IStructureCmp;
class ISequenceCmp;

class SSRegion : public CombinatoryRegion, public fideo::IStartProvider
{
    SecStructure wt_structure;
    SecStructure vaccine_structure;
    NMutations max_mutations;
    fideo::Similitude max_similitude;
    fideo::Distance min_distance;
    const NucSequencesCt wildtype_cache;
    const bool circ;

    /*libRNA backends*/
    fideo::IFold* const fold_backend;
    fideo::IFoldInverse* const inverse_backend;
    const fideo::IStructureCmp* const struct_cmp_backend;
    const ISequenceCmp* const seq_cmp_backend;

    virtual Score evaluate(const NucSequence&) const;
    virtual Score generate(NucSequence&, NucSequence&);
    virtual void set_base_sequence(const NucSequence& sequence);

    //Filters
    bool cache_compare(const NucSequence&);
    bool structure_compare(const NucSequence&);

    // Implements IStartProvider
    virtual void get_partial_start(fideo::IFoldInverse* const);
    virtual void get_complete_start(fideo::IFoldInverse* const);
public:
    SSRegion(SeqIndex, SeqIndex, const SecStructure&, const SecStructure&,
             NMutations, fideo::Similitude, fideo::Distance, const NucSequencesCt&, bool,
             fideo::IFold* const, fideo::IFoldInverse* const, const fideo::IStructureCmp* const,
             const ISequenceCmp* const);

};

#endif  /* _SSREGION_H */

