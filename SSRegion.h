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
#include "IFold.h"
#include "IFoldInverse.h"
#include "IStructureCmp.h"
#include "ISequenceCmp.h"
#include "ISequenceMutator.h"

class SSRegion : public CombinatoryRegion {    
    int max_mutations;
    float max_similitude;
    SecStructure wt_structure, vaccine_structure;
    int wt_seq_cache, min_distance;
    ISequenceMutator* mutator;
    
    /*libRNA backends*/
    IFold* fold_backend;
    IFoldInverse* inverse_backend;
    IStructureCmp* struct_cmp_backend;
    ISequenceCmp* seq_cmp_backend;
public:
    SSRegion(SecStructure, SecStructure, int, float, int, int,
            IFold&, IFoldInverse&, IStructureCmp&, ISequenceCmp&);
    
    void begin();
    float current(NucSequence& sequence);
    void next();
    bool done();
};

#endif	/* _SSREGION_H */

