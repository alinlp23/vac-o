/* 
 * File:   IQAEngine.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 3:48 PM 
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

#ifndef _IQAENGINE_H
#define	_IQAENGINE_H

#include "biopp.h"
#include "types.h"

class IQARegion;

/**
 * Interface for the quality assurance engine
 */
class IQAEngine
{
public:
    /**
     * Sets the depth for the QA.
     * @param d the desired depth.
     */
    virtual void set_depth(Depth d) = 0;
    /**
     * Add a QA region to the engine.
     * @param region pointer to a IQARegion.
     */
    virtual void add_region(IQARegion* region) = 0;
    /**
     * Validate a given ARN sequence
     * @param sequence the ARN sequence to validate.
     * @return If the sequence pass the QA or not.
     */
    virtual bool validate(const NucSequence& sequence) const = 0;

    virtual ~IQAEngine(){}
};


#endif	/* _IQAENGINE_H */

