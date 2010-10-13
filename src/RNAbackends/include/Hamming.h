/* 
 * File:   Hamming.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 1, 2010, 8:12 PM 
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

#ifndef _HAMMING_H
#define	_HAMMING_H

#include "ISequenceCmp.h"

/**
 * Very simple hamming distance implementation
 */
class Hamming : public ISequenceCmp
{
public:
    virtual Distance compare(const NucSequence&,
                             const NucSequence&) const throw(RNABackendException);
};


#endif	/* _HAMMING_H */

