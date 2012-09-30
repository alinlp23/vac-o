/*
 * File:   Solution.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 13, 2010, 9:00 PM
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

#ifndef _SOLUTION_H
#define _SOLUTION_H

#include "vaco-commons/ISolution.h"
#include "vaco-commons/ICombinatoryRegion.h"

class Solution : public ISolution
{
    NucSequence sequence;
    LocalOptimizationCt components;

    virtual void update_solution(RegionIdx, const NucSequence&, const LocalOptimization&);
    virtual void get_sequence(NucSequence&) const;
    virtual Score compute_local_score(RegionIdx) const;
    virtual ISolution* clone() const;
public:
    /**
     * Constructor
     * @param seq the ARN sequence
     * @param comps a container of solution components.
     * Useful to build the initial solution.
     */
    Solution(const NucSequence&, const CombinatoryRegionsCt&);

    Solution(const NucSequence&, const LocalOptimizationCt&);

};


#endif  /* _SOLUTION_H */

