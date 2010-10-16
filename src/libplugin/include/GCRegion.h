/* 
 * File:   GCRegion.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:31 PM 
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

#ifndef _GCREGION_H
#define	_GCREGION_H

#include "CombinatoryRegion.h"

class GCRegion : public CombinatoryRegion
{
    AminoSequence target_aminoacids;
    virtual Score evaluate(const NucSequence&) const;
    virtual Score generate(NucSequence&, NucSequence&);
public:
    GCRegion(SeqIndex, SeqIndex, const AminoSequence& aminoacids);
};

#endif	/* _GCREGION_H */

