/*
 * File:   SimulatedAnnealing.cpp
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 22, 2010, 4:26 PM
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

#include <cmath>
#include <iostream>
#include "vaco-libplugin/SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(const INeighborhood* ne, Iteration max, \
                                       Iteration max_idle, Iteration temp_up, Cooling c, Temperature t, Temperature cut):
    Strategy(ne, max, max_idle), temp_update(temp_up), temp_iter(), cooling(c),
    temperature(t), cutoff(cut), rnd(0.f, 1.f) {}

bool SimulatedAnnealing::select_neighbor()
{
    bool accept(false);
    if (!neighbors.empty())
    {
        const size_t neighbors_size = neighbors.size();
        const size_t idx = size_t(rnd.get() * (neighbors_size - 1));
        // Random neighbor
        const ISolution* nei = neighbors[idx].first;
        const Score nei_score = neighbors[idx].second;

        //If the neighbor has a better score than the current_score it's accepted.
        //otherwise, it's accepted with the following probability
        accept = nei_score >= current_score;
        if (!accept)
        {
            const float acceptance_prob = exp((nei_score - current_score) / temperature);
            const float r = rnd.get();
            accept = r < acceptance_prob;
        }

        if (accept)
        {
            selected_neighbor = nei;
            selected_neighbor_score = nei_score;
            for (size_t i = 0; i < neighbors_size; ++i)
            {
                if (i != idx)
                {
                    delete neighbors[i].first;
                }
            }
            neighbors.clear();
        }

        //Update temperature parameter.
        temp_iter++;
        if (temp_update == temp_iter)
        {
            temperature *= cooling;
            temp_iter = 0;
        }
    }
    return accept;
}

bool SimulatedAnnealing::update(const ISolution* neighbor)
{
    Score ns = scorer->evaluate(neighbor);
    ScoredSolution ss(neighbor, ns);
    insert_into(neighbors, ss);

    return false;
}

void SimulatedAnnealing::clean_up()
{
    Strategy::clean_up();
    const size_t neighbors_size = neighbors.size();
    for (size_t i = 0; i < neighbors_size; ++i)
    {
        delete neighbors[i].first;
    }
    neighbors.clear();
}

bool SimulatedAnnealing::done()
{
    return Strategy::done() || temperature < cutoff;
}
