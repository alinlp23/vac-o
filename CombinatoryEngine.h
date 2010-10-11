/* 
 * File:   CombinatoryEngine.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:08 PM 
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

#ifndef _COMBINATORYENGINE_H
#define	_COMBINATORYENGINE_H

#include <biopp/biopp.h>
#include "types.h"

#include "ISubject.h"
#include "ICombinatoryRegion.h"
#include "SequenceOptimization.h"
#include "Solution.h"

class IPlugin;
class INeighborhood;
class IStrategy;

class CombinatoryEngine : public ISingleObserver<ISolution>, public ISubject<SequenceOptimization>
{    
    const NucSequence sequence;
    const CutOff cutoff;
    CombinatoryRegionsCt regions;
    IPlugin* const plg;
    INeighborhood* neighborhood;
    IStrategy* strategy;

    /**
     * Implements the ISingleObserver interface.
     * Evaluate the solution using the plugin and
     * update the neighborhood of the strategy
     * @param s a new candidate solution
     * @return the same as the strategy update_neighbors function.
     */
    virtual bool update(const ISolution*);
public:
    /**
     * Constructor
     * @param seq the initial nucleotide sequence
     * @param rs the combinatory regions
     * @param c the threshold cutoff
     * @param plg the loaded plugin
     */
    CombinatoryEngine(const NucSequence&, const CombinatoryRegionsCt&,
                      CutOff, IPlugin* const);

    CombinatoryEngine(const CombinatoryEngine&);
    CombinatoryEngine& operator=(const CombinatoryEngine&);

    /**
     * Run the engine until plg->done() || strategy->done().
     * Will notify the observers for each sequence found.
     */
    void run();
};

#endif	/* _COMBINATORYENGINE_H */

