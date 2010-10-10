/* 
 * File:   IStrategy.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 9, 2010, 9:07 PM 
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

#ifndef _ISTRATEGY_H
#define	_ISTRATEGY_H

#include "types.h"
class Solution;

/**
 * Interface for local search strategies.
 */
class IStrategy
{
protected:
    Iteration current_iteration;
    Iteration best_iteration;
    Iteration max_idle_iterations;
    Iteration max_iterations;   
    
    virtual bool idle_iterations_expired() = 0;
    virtual bool max_iterations_expired() = 0;
public:
    /**
     * Base strategy constructor
     * @param max_idle maximum of idle iteration (iterations from the last improvement)
     * @param max_iter maximun of iterations
     */
    IStrategy(Iteration, Iteration);

    /**
     * Open a new iteration in the search proccess
     * @param current a pointer to the current solution.
     * @param score the score of current
     */
    virtual void open_iteration(const Solution*, Score) = 0;
    /**
     * Close the current iteration.
     */
    virtual void close_iteration() = 0;
    /**
     * Select a solution from the neighborhood explored in the current iteration.
     * Each concrete strategy would make the difference here.
     * @param score sets this parameter to the selected solution's score
     * @param improvement sets this parameter to true if the selected solution it's
     * a strict improvement, false otherwise.
     * @return a pointer to the selected solution
     */
    virtual const Solution* select_neighbor(Score&, bool&) = 0;
    /**
     * Update the neighborhood for the current iteration
     * @param n a new candidate solution neighbor
     * @param score the neighbor's score
     * @return true to keep exploring the neighborhood, false otherwise.
     */
    virtual bool update_neighbors(const Solution*, Score) = 0;
    /**
     * Decides when to stop the local search
     * @return true to stop the search
     */
    virtual bool done() const = 0;

    virtual ~IStrategy(){}
};


#endif	/* _ISTRATEGY_H */

