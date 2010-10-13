/* 
 * File:   INeighborhood.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 9, 2010, 8:03 PM 
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

#ifndef _INEIGHBORHOOD_H
#define	_INEIGHBORHOOD_H

#include "ISubject.h"
#include "ISolution.h"
#include "ICombinatoryRegion.h"

/**
 * Interface for neighborhoods implementations.
 */
class INeighborhood : public ISingleSubject<ISolution>
{
protected:
    CombinatoryRegionsCt regions;
public:
    /**
     * Constructor
     * @param regions
     */
    INeighborhood(const CombinatoryRegionsCt&);

    /**
     * Explore the neighborhood of a given solution and notify the observer
     * for each solution found.
     * @param s a solution pointer
     */
    virtual void explore(const ISolution* const) = 0;
};

#endif	/* _INEIGHBORHOOD_H */

