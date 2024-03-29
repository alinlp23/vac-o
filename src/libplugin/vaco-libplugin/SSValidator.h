/*
 * File:   SSValidator.h
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

#ifndef _SSVALIDATOR_H
#define _SSVALIDATOR_H

#include "fideo/RnaBackendsTypes.h"
#include "fideo/IFold.h"
#include "fideo/IStructureCmp.h"
#include "biopp/biopp.h"

#include "vaco-libplugin/SimilitudeCmp.h"
#include "vaco-libplugin/IQAValidator.h"

template<SimilitudePolicy policy>
class SSValidator : public IQAValidator
{
    fideo::IFold* const fold_backend;
    const fideo::IStructureCmp* const struct_cmp_backend;

    const biopp::SecStructure target_structure;
    const fideo::Similitude similitude;
    const bool circ;

    /**
     * Validate a sequence, doing the folding and comparing the
     * two structures.
     * @param seq the sequence to validate
     * @return It depends on cmp_policy if it check for maxium o minium similitude.
     */
    virtual bool validate(const biopp::NucSequence&) const;
public:
    /**
     * Constructor
     * @param fb fold backend
     * @param strb Structure compare backend
     * @param structure Target secondary structure
     * @param simil Target similitude
     */
    SSValidator(fideo::IFold*, const fideo::IStructureCmp*, const biopp::SecStructure&, fideo::Similitude, bool);
};

//Implementation

template<SimilitudePolicy policy>
SSValidator<policy>::SSValidator(fideo::IFold* fb, const fideo::IStructureCmp* strb, const biopp::SecStructure& str, fideo::Similitude simil, bool circ)
    : fold_backend(fb),
      struct_cmp_backend(strb),
      target_structure(str),
      similitude(simil),
      circ(circ)
{}

template<SimilitudePolicy policy>
bool SSValidator<policy>::validate(const biopp::NucSequence& seq) const
{
    biopp::SecStructure seq_struct;
    fold_backend->fold(seq, circ, seq_struct);

    bool pass(true);
    if (seq_struct.pair_count() > 0)
    {
        const fideo::Similitude s = struct_cmp_backend->compare(target_structure, seq_struct);
        pass = SimilitudeCmp<policy>::cmp(similitude, s);
    }
    return pass;
}

#endif  /* _SSVALIDATOR_H */

