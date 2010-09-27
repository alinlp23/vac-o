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

class ICombinatoryRegion {
public:
    virtual void begin() = 0;
    virtual float current(NucSequence& sequence) = 0;
    virtual void next() = 0;
    virtual bool done() = 0;

    virtual void set_base_sequence(NucSequence sequence) = 0;
    virtual void add_constraint(int start, int end) = 0;

    virtual ~ICombinatoryRegion(){}
};

#endif	/* _ICOMBINATORYREGION_H */

