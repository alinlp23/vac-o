/*
 * File:   RNAFoldInverse.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 2, 2010, 1:28 PM
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

#ifndef _RNAINVERSE_H
#define	_RNAINVERSE_H

#include "RNAStartInverse.h"
#include "RNABackendProxy.h"

class RNAinverse : public RNAStartInverse
{
    static const Path IN;
    static const Path OUT;
    static Command CMD;
    static const FileLineNo LINE_NO;

    size_t read_hamming_distance(FileLine&, size_t, Distance&) const throw(RNABackendException);
    size_t read_structure_distance(FileLine&, size_t, Similitude&) const throw(RNABackendException);
    
    virtual void execute(string&, Distance&, Similitude&) throw(RNABackendException);
    virtual void query_start(IStartProvider*) throw(RNABackendException);
public:
    RNAinverse(const SecStructure&, Similitude, Distance, Attempts);
};

#endif	/* _RNAINVERSE_H */

