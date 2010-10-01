/* 
 * File:   ISequenceOptimization.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 30, 2010, 4:58 PM 
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

#ifndef _ISEQUENCEOPTIMIZATION_H
#define	_ISEQUENCEOPTIMIZATION_H

#include "biopp.h"
#include "types.h"

class SequenceOptimization
{
    NucSequence sequence;
    Score score;
public:
    /**
     * Constructor
     * @param the optimized sequence.
     * @param the sequence's score.
     */
    SequenceOptimization(NucSequence&, Score);
    /**
     * Gets the sequence
     * @param NucSequence to write to.
     */
    inline void get_sequence(NucSequence&) const;
    /**
     * Gets the global score of the optimization.
     * @return The score.
     */
    inline Score get_score() const;
    /**
     * Compare two sequence optimizations
     * @param a sequence optimization
     * @param another sequence optimization
     * @return If the first it's less than the second.
     */
    inline bool operator() (const SequenceOptimization*,
                            const SequenceOptimization*) const;    
};

#endif	/* _ISEQUENCEOPTIMIZATION_H */

