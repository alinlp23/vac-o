/* 
 * File:   TripletsProductor.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 29, 2010, 12:06 PM 
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

#ifndef _TRIPLETSPRODUCTOR_H
#define	_TRIPLETSPRODUCTOR_H

#include <vector>
#include <biopp/biopp.h>

using std::vector;

/**
 * Iterates over the cartesian product for all the triplets of each
 * aminoacid in the given AminoSequence
 */
class TripletsProductor
{
public:
    typedef vector<Triplet> TripletsProduct;
    TripletsProductor(const AminoSequence& aminoacids);
    bool next(TripletsProduct& p);
private:
    const size_t last;
    bool more;
    vector<TripletsIterator> prod_it;
    TripletsProduct product;

    void move(size_t i);
};

#endif	/* _TRIPLETSPRODUCTOR_H */

