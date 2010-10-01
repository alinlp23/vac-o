/* 
 * File:   SequenceEvaluator.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 30, 2010, 9:22 PM 
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

#ifndef _SEQUENCEEVALUATOR_H
#define	_SEQUENCEEVALUATOR_H

#include "biopp.h"
#include "IObserver.h"
#include "ISubject.h"
#include "SequenceOptimization.h"
#include "IPlugin.h"


class SequenceEvaluator : public IObserver<NucSequence>, public ISubject<SequenceOptimization>
{
    const IPlugin* const plg;
    /**
     * Implements the IObserver<NucSequence> interface.
     * Evaluate the sequence and notify the observers.
     * @param the sequence to be evaluated.
     */
    virtual void update(const NucSequence*);
public:
    SequenceEvaluator(const IPlugin*);
    SequenceEvaluator(const SequenceEvaluator&);
    SequenceEvaluator& operator=(const SequenceEvaluator&);
};

#endif	/* _SEQUENCEEVALUATOR_H */

