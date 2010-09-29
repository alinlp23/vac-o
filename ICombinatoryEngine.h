/* 
 * File:   ICombinatoryEngine.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:07 PM 
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

#ifndef _ICOMBINATORYENGINE_H
#define	_ICOMBINATORYENGINE_H

#include "biopp.h"
#include "types.h"

class ICombinatoryRegion;

/**
 * Interface for the combinatory engine.
 */
class ICombinatoryEngine
{
public:
    /**
     * Run the engine.
     */
    virtual void run() = 0;
    /**
     * Add a new combinatory region to the engine.
     * @param region pointer to a combinatory region     
     */
    virtual void add_region(ICombinatoryRegion* region) = 0;
    /**
     * Sets the initial ARN sequence.
     * @param sequence reference to a NucSequence
     */
    virtual void set_sequence(const NucSequence& sequence) = 0;
    /**
     * Sets the threshold cutoff.
     * @param c floating point between 0 and 1
     */
    virtual void set_cutoff(CutOff c) = 0;

    virtual ~ICombinatoryEngine(){}
};

#endif	/* _ICOMBINATORYENGINE_H */

