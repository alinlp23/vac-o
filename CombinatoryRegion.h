/* 
 * File:   CombinatoryRegion.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:09 PM 
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

#ifndef _COMBINATORYREGION_H
#define	_COMBINATORYREGION_H

#include <list>
#include "biopp.h"
#include "ICombinatoryRegion.h"

using std::list;

class CombinatoryRegion : public ICombinatoryRegion
{
    struct Constraint{
        SeqPosition start, end;
    };
    list<Constraint> constraints;
    SeqPosition start, end;
    NucSequence base_sequence;
public:
    void set_base_sequence(const NucSequence& sequence);
    void add_constraint(SeqPosition start, SeqPosition end);
};


#endif	/* _COMBINATORYREGION_H */

