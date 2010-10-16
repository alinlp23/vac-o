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
#include "SequenceOptimization.h"
#include "ISolution.h"
#include "IPlugin.h"

class IStrategy;

class CombinatoryEngine : public ISolutionObserver, public ISubject<SequenceOptimization>
{
    IPlugin* const plg;
    IStrategy* strategy;
    ISolutionScorer* ssadapter;

    class PluginScoreAdapter: public ISolutionScorer
    {
        IPlugin* plg;
        virtual Score evaluate(const ISolution* sol) const
        {
            return plg->evaluate_solution(sol);
        }
    public:
        PluginScoreAdapter(IPlugin* p) : plg(p) {}
        PluginScoreAdapter(const PluginScoreAdapter&);
        PluginScoreAdapter& operator=(const PluginScoreAdapter&);
    };

    /**
     * Implements the ISingleObserver interface.
     * Evaluate the solution using the plugin and
     * update the neighborhood of the strategy
     * @param solution a new candidate solution
     * @param score the score assigned
     */
    virtual void update(const ISolution*, Score);
public:
    /**
     * Constructor
     * @param plg the loaded plugin
     */
    CombinatoryEngine(IPlugin* const);

    CombinatoryEngine(const CombinatoryEngine&);
    CombinatoryEngine& operator=(const CombinatoryEngine&);

    /**
     * Run the engine until plg->done() || strategy->done().
     * Will notify the observers for each sequence found.
     */
    void run_forest();

    ~CombinatoryEngine();
};

#endif	/* _COMBINATORYENGINE_H */

