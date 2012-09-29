/*
 * File:   CombinatoryEngine.cpp
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

#include <iostream>
#include "vaco-commons/IStrategy.h"
#include "vaco-core/CombinatoryEngine.h"

using std::cout;
using std::endl;

CombinatoryEngine::CombinatoryEngine(IPlugin* const plg) :
    plg(plg), strategy(plg->get_strategy()), ssadapter()
{
    ssadapter = new PluginScoreAdapter(plg);
    strategy->set_scorer(ssadapter);
}

void CombinatoryEngine::run_forest()
{
    cout << "Running Combinatory engine..." << endl;
    strategy->run(plg->get_initial_solution(), this);
}

void CombinatoryEngine::update(const ISolution* const solution, Score score)
{
    NucSequence sequence;
    solution->get_sequence(sequence);
    notify(new SequenceOptimization(sequence, score));
}

CombinatoryEngine::~CombinatoryEngine()
{
    delete ssadapter;
}
