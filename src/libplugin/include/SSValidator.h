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
#define	_SSVALIDATOR_H

#include "rna_backends_types.h"
#include "IQAValidator.h"

class IStructureCmp;
class IFold;

enum SimilitudePolicy
{
    MinSimilitude, MaxSimilitude
};

class SSValidator : public IQAValidator
{
    const IFold* const fold_backend;
    const IStructureCmp* const struct_cmp_backend;

    const SecStructure target_structure;
    const Similitude similitude;
    const SimilitudePolicy cmp_policy;

    /**
     * Validate a sequence, doing the folding and comparing the
     * two structures.
     * @param seq the sequence to validate
     * @return It depends on cmp_policy if it check for maxium o minium similitude.
     */
    virtual bool validate(const NucSequence&) const;
public:
    /**
     * Constructor
     * @param fb fold backend
     * @param strb Structure compare backend
     * @param structure Target secondary structure
     * @param simil Target similitude
     * @param sp The similitude policy.
     */
    SSValidator(const IFold*, const IStructureCmp*, const SecStructure&, Similitude, SimilitudePolicy);
};


#endif	/* _SSVALIDATOR_H */

