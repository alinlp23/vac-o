/*
 * File:   IQARegion.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 3:46 PM
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

#ifndef _IQAREGION_H
#define _IQAREGION_H

#include <list>
#include "vaco-commons/types.h"

using std::list;

/**
 * Interface for quality assurance regions.
 */
class IQARegion
{
public:
    /**
     * Validate a given ARN sequence.
     * @param sequence the ARN sequence to validate.
     * @return If the sequence pass the QA or not.
     */
    virtual bool validate(const NucSequence& sequence) const = 0;

    virtual ~IQARegion() {}
};

/**
 * Container of IQARegion
 */
typedef list<IQARegion*> QARegionsCt;

#endif  /* _IQAREGION_H */

