/*
 * File:   Neighborhood.cpp
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

#include "vaco-libplugin/Neighborhood.h"

Neighborhood::Neighborhood(const CombinatoryRegionsCt& r, CutOff c, Attempts a):
    regions(r), cutoff(c), attempts(a)
{}

void Neighborhood::explore(const ISolution* current) const
{
    NucSequence cseq;
    current->get_sequence(cseq);
    RegionIdx r = 0;
    bool done(false);

    while (r < regions.size() && !done)
    {
        //sets the current solution's sequence as the base sequence
        regions[r]->set_base_sequence(cseq);
        //Compute local score without the region r
        const Score cscore = current->compute_local_score(r);

        Attempts i = 0;
        while (i < attempts && !done)
        {
            NucSequence nseq;
            NucSequence ndelta;
            Score nscore = regions[r]->generate(nseq, ndelta);

            if (cscore* nscore >= cutoff)
            {
                ISolution* const neighbor = current->clone();
                LocalOptimization op(ndelta, nscore);
                neighbor->update_solution(r, nseq, op);
                done = notify(neighbor);
            }
            ++i;
        }
        ++r;
    }
}

