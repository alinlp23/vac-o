/*
 * File:   TripletsProductor.cpp
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

#include "TripletsProductor.h"

TripletsProductor::TripletsProductor(const AminoSequence& aminoacids) :
    last(aminoacids.size() - 1), more(aminoacids.size() > 0),
    prod_it(aminoacids.size()), product(aminoacids.size())
{
    for (size_t i = 0; i < aminoacids.size(); ++i)
    {
        TripletsIterator triplet_it = GeneticCode::triplets(aminoacids[i]);
        prod_it[i] = triplet_it;
        product[i] = *(prod_it[i]);

    }
}
bool TripletsProductor::next(TripletsProduct& p)
{
    bool cont(more);
    p = product;
    if (more)
        move(last);

    return cont;
}

void TripletsProductor::move(size_t i)
{
    ++prod_it[i];
    if (prod_it[i].end())
    {
        prod_it[i].restart();
        if (i > 0)
            move(i - 1);
        else
            more = false;
    }
    product[i] = *(prod_it[i]);
}

