/*
 * File:   Strategy.cpp
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

#include "Strategy.h"

Strategy::Strategy(const INeighborhood* ne, Iteration max, Iteration max_idle):
    neighborhood(ne), scorer(), max_iterations(max), max_idle_iterations(max_idle),
    current_iteration(0), best_iteration(0), current_solution(), selected_neighbor(),
    selected_neighbor_score(), current_score()
{}

void Strategy::set_scorer(const ISolutionScorer* s)
{
    scorer = s;
}

void Strategy::run(const ISolution* init, ISolutionObserver* obs)
{
    current_solution = init;
    current_score = scorer->evaluate(current_solution);
    while (!done())
    {
        ++current_iteration;
        neighborhood->explore(current_solution);

        bool someone_selected = select_neighbor();
        if (someone_selected)
        {
            if (selected_neighbor_score >= current_score)
            {
                obs->update(selected_neighbor, selected_neighbor_score);

                if (selected_neighbor_score > current_score)
                    best_iteration = current_iteration;

            }

            delete current_solution;
            current_solution = selected_neighbor;
            current_score = selected_neighbor_score;
        }
    }
    //Final clean up
    clean_up();
    if (selected_neighbor)
        delete selected_neighbor;
    else
    {
        /*
         * Just to be complete... if this is the case,
         * the local search ended without any neighbor found.
         */
        delete init;
    }
}

bool Strategy::max_idle_iterations_expired() const
{
    return current_iteration - best_iteration >= max_idle_iterations;
}

bool Strategy::max_iterations_expired() const
{
    return current_iteration >= max_iterations;
}

bool Strategy::done()
{
    return max_idle_iterations_expired() || max_iterations_expired();
}

void Strategy::clean_up()
{}
