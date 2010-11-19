/*
 * File:   Solution.cpp
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

#include "Solution.h"

Solution::Solution(const NucSequence& seq, const CombinatoryRegionsCt& regions):sequence(seq), components()
{
    CAutonomousIterator<CombinatoryRegionsCt> it(regions);
    SeqIndex start;
    SeqIndex end;
    while (!it.end())
    {
        (*it)->get_bounds(start, end);
        string c;
        for (size_t idx=start; idx<end; ++idx)
        {
            c.append(to_str(seq[idx]));
        }
        //default local score = 1
        LocalOptimization op(c, 1);
        insert_into(components, op);
        ++it;
    }
}

Solution::Solution(const NucSequence& seq, const LocalOptimizationCt& comp) :
        sequence(seq), components(comp)
{}

void Solution::update_solution(RegionIdx r, const NucSequence& seq, const LocalOptimization& op) throw(PluginException)
{
    if (r < components.size() && seq.length() == sequence.length())
    {
        components[r] = op;
        sequence = seq;
    }
    else
        throw(PluginException(" Out of range while updating solution component"));
}

void Solution::get_sequence(NucSequence& seq) const
{
    seq = sequence;
}

Score Solution::compute_local_score(RegionIdx exclude) const
{
    Score score = 1;
    for (RegionIdx i = 0; i<components.size(); ++i)
    {
        if (i != exclude)
            score *= components[i].second;

        ++i;
    }
    return score;
}

ISolution* Solution::clone() const
{
    return new Solution(sequence, components);
}
