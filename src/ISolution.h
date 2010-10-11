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
#include <biopp/biopp.h>
#include "types.h"
#include "ICombinatoryRegion.h"

using std::map;

typedef pair<NucSequence, Score> LocalOptimization;

/**
 * Solutions represents the search space in any local search strategy.
 * Each solution, has the complete sequence and a map between
 * regions and optimizations.
 */
class ISolution
{    
public:
    /**
     * Constructor
     * @param seq the ARNl sequence
     * @param comps a map of it's components
     */
    ISolution(const NucSequence&, const map<const ICombinatoryRegion*, LocalOptimization>&);
    
    /**
     * Constructor
     * @param seq the ARN sequence
     * @param comps a container of solution components. 
     * Useful to build the initial solution.
     */
    ISolution(const NucSequence&, const NucSequencesCt&);

    /**
     * Update this solution in a given component.
     * @param r the region to be updated
     * @param seq the new complete sequence
     * @param op the local optimization for the region being updated.
     */
    virtual void update_solution(const ICombinatoryRegion* const, const NucSequence&, const LocalOptimization&) = 0;

    /**
     * Gets the complete sequence of this solution
     * @param seq the sequence
     */
    virtual void get_sequence(NucSequence&) const = 0;

    /**
     * Compute the local score for this solution excluding a given region.
     * @param exclude the region to be excluded from the score.
     * @return the partial local score without the region excluded.
     */
    virtual Score compute_local_score(const ICombinatoryRegion* const) const = 0;

    /**
     * Clone this solution
     * @return The new solution.
     */
    virtual ISolution* clone() const = 0;

    virtual ~ISolution(){}
};



#endif	/* _SOLUTION_H */

