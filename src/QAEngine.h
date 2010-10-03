/* 
 * File:   QAEngine.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 3:52 PM 
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

#ifndef _QAENGINE_H
#define	_QAENGINE_H

#include "biopp.h"
#include "types.h"

#include "ISubject.h"
#include "IObserver.h"
#include "IQARegion.h"

class IPlugin;

class QAEngine : public IObserver<NucSequence>, public ISubject<NucSequence>
{    
    Depth depth;
    QARegionsCt regions;
    /**
     * Implements the IObserver<NucSequence> interface.
     * If the sequence pass the QA, will notify the observers.
     * @param candidate the sequence to be validated.
     */
    virtual void update(const NucSequence*);
    /**
     * Validate a given sequence
     * @param sequence the NucSequence to validate.
     * @return If the sequnce pass or not the QA.
     */
    bool validate(const NucSequence&) const;
public:
    /**
     * Constructor will ask the plugin for needed data.
     * @param depth the depth for the QA tree
     * @param regions the QA regions
     */
    QAEngine(Depth, const QARegionsCt&);
};

#endif	/* _QAENGINE_H */

