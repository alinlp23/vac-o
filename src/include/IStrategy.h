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
#include "ISubject.h"
#include "ISolution.h"

/**
 * Interface for solution scorer
 */
struct ISolutionScorer
{
    /**
     * Evaluate a given solution.
     * @param sol the solution to be evaluated.
     * @return the score assigned.
     */
    virtual Score evaluate(const ISolution*) const = 0;
    virtual ~ISolutionScorer(){}
};

struct ISolutionObserver
{
    virtual void update(const ISolution* const, Score) = 0;
    virtual ~ISolutionObserver(){}
};

/**
 * Interface for local search strategies.
 */
class IStrategy : public ISingleObserver<ISolution>
{
public:
    /**
     * Run the local search for an initial solution.
     * @param solution the initial solution
     * @param observer an observer to noitify new improvements.
     */
    virtual void run(const ISolution*, ISolutionObserver*) = 0;

    /**
     * Sets the solution scorer to be used during the search.
     * @param
     */
    virtual void set_scorer(const ISolutionScorer*) = 0;

    virtual ~IStrategy(){}
};


#endif	/* _ISTRATEGY_H */

