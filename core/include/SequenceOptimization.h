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
#define _ISEQUENCEOPTIMIZATION_H

#include <biopp/biopp.h>

#include "types.h"
#include <utility>
using std::pair;

typedef pair<NucSequence, Score> SequenceOptimization;

struct SequenceOptimizationCmp
{
    /**
     * Compare two sequence optimizations
     * @param opt1 a sequence optimization
     * @param opt2 another sequence optimization
     * @return If the first it's greater than the second.
     */
    bool operator()(const SequenceOptimization*,
                    const SequenceOptimization*) const;
};


#endif  /* _ISEQUENCEOPTIMIZATION_H */

