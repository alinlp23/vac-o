/* 
 * File:   ICombinatoryRegion.h
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

#ifndef _ICOMBINATORYREGION_H
#define	_ICOMBINATORYREGION_H

#include "biopp.h"
#include "types.h"

/**
 * Interface for combinatories regions.
 */
class ICombinatoryRegion
{
public:
    /**
     * Sets the iterator at the beginning.
     */
    virtual void begin() = 0;
    /**
     * Gets the current sequence.
     * @param sequence the NucSequence reference to write to.
     * @return The score of the sequence
     */
    virtual Score current(NucSequence& sequence) = 0;
    /**
     * Move the iterator forwards
     */
    virtual void next() = 0;
    /**
     * Check if there are more sequences.
     * @return If the iterator it's done or not.
     */
    virtual bool done() const = 0;
    /**
     * Sets the base sequence of the region.
     * @param sequence the ARN sequence
     */
    virtual void set_base_sequence(const NucSequence& sequence) = 0;
    /**
     * Add a constraint to the region.
     * @param start index where the constraint starts
     * @param end index where the constraint ends
     */
    virtual void add_constraint(SeqIndex start, SeqIndex end) = 0;

    virtual ~ICombinatoryRegion(){}
};

#endif	/* _ICOMBINATORYREGION_H */

