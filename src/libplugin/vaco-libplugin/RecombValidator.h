/*
 * File:   RecombValidator.h
 * Author: Facundo Munoz <facuu.munoz at gmail.com>
 *
 *
 * Copyright (C) 2012  Facundo Munoz, FuDePAN
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

#ifndef _RecombValidator_H
#define _RecombValidator_H

#include "fideo/RnaBackendsTypes.h"
#include "fideo/IFold.h"
#include "fideo/IStructureCmp.h"
#include "biopp/biopp.h"

#include "vaco-commons/RecombinantInfo.h"
#include "vaco-libplugin/SimilitudeCmp.h"
#include "vaco-libplugin/IQAValidator.h"
#include "vaco-libplugin/RecombAlgorithm.h"

template<SimilitudePolicy policy>
class RecombValidator : public IQAValidator
{
    const RecombinantInfo& recombInfo;
    fideo::IFold& fold_backend;
    const fideo::IStructureCmp& struct_cmp_backend;
    const SecStructure& wt_struct;
    const fideo::Similitude similitude;

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
     * @param simil Target similitude
     */
    RecombValidator(const RecombinantInfo& recombInfo, fideo::IFold& fb, const fideo::IStructureCmp& strb, const SecStructure& wt_struct, fideo::Similitude simil);

    virtual ~RecombValidator()
    {}
};

//Implementation

template<SimilitudePolicy policy>
RecombValidator<policy>::RecombValidator(const RecombinantInfo& recombInfo, fideo::IFold& fb, const fideo::IStructureCmp& strb, const SecStructure& wt_struct, fideo::Similitude simil)
    : recombInfo(recombInfo),
      fold_backend(fb),
      struct_cmp_backend(strb),
      wt_struct(wt_struct),
      similitude(simil)
{}

template<SimilitudePolicy policy>
bool RecombValidator<policy>::validate(const biopp::NucSequence& seq) const
{
    RecombAlgorithm algorithm(recombInfo, seq);

    std::list<biopp::NucSequence> results;
    //call to Recomb algorithm
    algorithm.run(results);

    bool pass(true);
    std::list<biopp::NucSequence>::const_iterator it = results.begin();
    while(it != results.end() && pass)
    {
        biopp::SecStructure seq_struct;
        const bool circ = false;
        fold_backend.fold(*it, circ, seq_struct);

        if (seq_struct.pair_count() > 0)
        {
            const fideo::Similitude s = struct_cmp_backend.compare(wt_struct, seq_struct);
            pass = SimilitudeCmp<policy>::cmp(similitude, s);
        }
        ++it;
    }

    return pass;
}


#endif  /* _RecombValidator_H */

