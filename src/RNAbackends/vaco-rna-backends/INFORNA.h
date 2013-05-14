/*
 * File:   INFORNA.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 25, 2010, 1:36 PM
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

#ifndef _INFORNA_H
#define _INFORNA_H

#include <string>
#include "vaco-rna-backends/RNAStartInverse.h"

class INFORNA : public RNAStartInverse
{
    static const FilePath OUT;
    static const FileLineNo LINE_NO;
    static const std::string INFORNA_PROG;

    size_t read_sequence(FileLine&, size_t, string&) const throw(RNABackendException);
    size_t read_hamming_distance(FileLine&, size_t, Distance&) const throw(RNABackendException);
    size_t read_structure_distance(FileLine&, size_t, Similitude&) const throw(RNABackendException);

    virtual void execute(string&, Distance&, Similitude&) throw(RNABackendException);
    virtual void query_start(IStartProvider*) throw(RNABackendException);
public:
    INFORNA(const biopp::SecStructure&, Similitude, Distance, CombinationAttempts);
};

#endif  /* _INFORNA_H */

