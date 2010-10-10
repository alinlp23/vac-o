/* 
 * File:   Solution.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 9, 2010, 7:48 PM 
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
#define	_SOLUTION_H

#include <map>
#include "biopp.h"
#include "types.h"
#include "ICombinatoryRegion.h"

using std::map;

typedef pair<NucSequence, Score> LocalOptimization;

/**
 * Solutions represents the search space in any local search strategy.
 * Each solution, has the complete sequence and a map between
 * regions and optimizations.
 */
class Solution
{
    NucSequence sequence;    
    map<ICombinatoryRegion*, LocalOptimization> components;
public:
    /**
     * Constructor
     * @param seq the initial sequence
     * @param comps a map of it's components
     */
    Solution(NucSequence&, map<ICombinatoryRegion*, LocalOptimization>);

    /**
     * Update this solution in a given component.
     * @param r the region to be updated
     * @param seq the new complete sequence
     * @param op the local optimization for the region being updated.
     */
    void update_solution(ICombinatoryRegion*, NucSequence&, LocalOptimization&);

    /**
     * Gets the complete sequence of this solution
     * @param seq the sequence
     */
    void get_sequence(NucSequence& seq) const;

    /**
     * Compute the local score for this solution excluding a given region.
     * @param exclude the region to be excluded from the score.
     * @return the partial local score without the region excluded.
     */
    Score compute_local_score(const ICombinatoryRegion* exclude) const;    
};



#endif	/* _SOLUTION_H */

