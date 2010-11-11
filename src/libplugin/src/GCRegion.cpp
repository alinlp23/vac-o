/*
 * File:   GCRegion.cpp
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

#include "GCRegion.h"

GCRegion::GCRegion(SeqIndex s, SeqIndex e, const AminoSequence& aminoacids) :
        CombinatoryRegion(s, e), target_aminoacids(aminoacids),
        productor(new TripletsProductor(aminoacids)), rbase()
{}

GCRegion::~GCRegion()
{
    delete productor;
}

Score GCRegion::evaluate(const NucSequence& delta) const
{
    return 1.f;
}

Score GCRegion::generate(NucSequence& sequence, NucSequence& delta)
{
    TripletsProductor::TripletsProduct current_prod;    
    string raw;
    delta = rbase;
    const size_t ntriplets = delta.triplets_length();
    do
    {
        productor->next(current_prod);
        raw.clear();
        for (size_t i=0; i< ntriplets; ++i)
        {
            delta.set_triplet(i, current_prod[i]);
            raw += current_prod[i].to_string();
        }
    }
    while (raw == rbase);

    sequence = base_sequence;
    for (size_t idx=0; idx<delta.length(); ++idx)
        sequence[start+idx] = delta[idx];

    return evaluate(delta);
}

void GCRegion::set_base_sequence(const NucSequence& seq)
{
    base_sequence = seq;
    rbase.clear();
    for (size_t i=start; i<end; ++i)
    {
        rbase+=to_str(base_sequence[i]);
    }    
}