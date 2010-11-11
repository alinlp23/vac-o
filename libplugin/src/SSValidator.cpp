/*
 * File:   SSValidator.cpp
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

#include "IFold.h"
#include "IStructureCmp.h"
#include "SSValidator.h"

SSValidator::SSValidator(const IFold* fb, const IStructureCmp* strb, 
        const SecStructure& str, Similitude simil, SimilitudePolicy sp) :
        fold_backend(fb), struct_cmp_backend(strb), target_structure(str),
        similitude(simil), cmp_policy(sp)
{}

bool SSValidator::validate(const NucSequence& seq) const
{
    SecStructure seq_struct;
    fold_backend->fold(seq, seq_struct);
    const Similitude s = struct_cmp_backend->compare(target_structure, seq_struct);
    
    return cmp_policy == MinSimilitude ? similitude <= s : similitude >= s;
}
