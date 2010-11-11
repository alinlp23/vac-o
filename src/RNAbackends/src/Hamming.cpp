/*
 * File:   Hamming.cpp
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 10, 2010, 4:26 PM
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

#include "Hamming.h"

Hamming::Hamming() : matrix()
{
    initialize_distance_matrix(matrix);
}

Hamming::Hamming(const IDistanceMatrixProvider* const provider) : matrix()
{
    initialize_distance_matrix(matrix);
    provider->get_distance_matrix(matrix);
}

Distance Hamming::compare(const NucSequence& seq1,
                          const NucSequence& seq2) const throw(RNABackendException)
{
    
    if (seq1.length() != seq2.length())
        throw RNABackendException("Hamming distance must be calculated over sequences of the same size");
    
    Distance h = 0.f;
    const size_t n_triplets = seq1.triplets_length();
    for (size_t i=0; i<n_triplets; ++i)
    {
        const Triplet t1 = seq1.get_triplet(i);
        const Triplet t2 = seq2.get_triplet(i);

        h += t1.distance(t2, matrix);
    }
           
    return h;
}

