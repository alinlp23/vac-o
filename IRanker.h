/* 
 * File:   IRanker.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 3:58 PM 
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

#ifndef _IRANKER_H
#define	_IRANKER_H

#include "biopp.h"
#include "types.h"

/**
 * Interface for the sequences ranker.
 */
class IRanker
{
public:
    /**
     * Update the ranking with a new sequence and score.
     * @param sequence the new ARN sequence.
     * @param s the score assigned to the new sequence.
     */
    virtual void update(const NucSequence& sequence, Score s) = 0;
    /**
     * Sets the iterator at the beginning.
     */
    virtual void begin() = 0;
    /**
     * Gets the current sequence and score.
     * @param sequence the NucSequence to write to.
     * @return The score assigned to the current sequence.
     */
    virtual Score current(NucSequence& sequence) = 0;
    /**
     * Move the iterator forwards.
     */
    virtual void next() = 0;
    /**
     * Check if there are more sequences.
     * @return If the iterator it's done or not.
     */
    virtual bool done() const = 0;

    virtual ~IRanker(){}
};

#endif	/* _IRANKER_H */

