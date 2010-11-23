/* 
 * File:   SimulatedAnnealing.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 22, 2010, 5:28 PM 
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

#ifndef _SIMULATEDANNEALING_H
#define	_SIMULATEDANNEALING_H

#include "Strategy.h"
#include <utility>
#include <vector>
#include <mili/mili.h>

class SimulatedAnnealing : public Strategy
{
    virtual void clean_up();
    virtual bool select_neighbor();
    virtual bool done();
    virtual bool update(const ISolution*);  

    typedef float Temperature;
    typedef float Cooling;
    typedef std::pair<const ISolution*, Score> ScoredSolution;

    std::vector<ScoredSolution> neighbors;
    Iteration temp_update;
    Iteration temp_iter;
    Cooling cooling;
    Temperature temperature;
    Temperature cutoff;
    Randomizer<float> rnd;
public:
    SimulatedAnnealing(const INeighborhood*, Iteration, Iteration, Iteration, Cooling, Temperature, Temperature);
};

#endif	/* _SIMULATEDANNEALING_H */

