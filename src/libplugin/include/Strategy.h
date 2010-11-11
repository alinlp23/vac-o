/*
 * File:   Strategy.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 13, 2010, 10:23 PM
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

#ifndef _STRATEGY_H
#define	_STRATEGY_H

#include "IStrategy.h"
#include "INeighborhood.h"

/**
 * Base class implementation for local search strategies.
 */
class Strategy : public IStrategy
{
    virtual void set_scorer(const ISolutionScorer*);
protected:
    const INeighborhood* neighborhood;
    const ISolutionScorer* scorer;
    Iteration max_iterations;
    Iteration max_idle_iterations;
    Iteration current_iteration;
    Iteration best_iteration;

    const ISolution* current_solution;
    const ISolution* selected_neighbor;
    Score selected_neighbor_score;
    Score current_score;

    bool max_idle_iterations_expired() const ;
    bool max_iterations_expired() const;

    virtual void run(const ISolution*, ISolutionObserver*);
    virtual bool done();

    virtual bool select_neighbor() = 0;
public:
    Strategy(const INeighborhood*, Iteration, Iteration);    
};


#endif	/* _STRATEGY_H */

