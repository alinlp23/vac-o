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

#include "ICombinatoryRegion.h"

class ICombinatoryEngine {
public:
    virtual void run() = 0;
    virtual void add_region(ICombinatoryRegion& region) = 0;
    virtual void set_sequence(NucSequence sequence) = 0;
    virtual void set_cutoff(float cutoff) = 0;

    virtual ~ICombinatoryEngine(){}
};

#endif	/* _ICOMBINATORYENGINE_H */

