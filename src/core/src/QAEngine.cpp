/*
 * File:   QAEngine.cpp
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
#include <mili/mili.h>
#include "vaco-core/QAEngine.h"

using std::cout;
using std::endl;

QAEngine::QAEngine(const QARegionsCt& regions):
    regions(regions)
{}

void QAEngine::update(const SequenceOptimization* candidate)
{
    cout << "QA validation for: ";
    for (size_t i = 0; i < (candidate->first).length(); ++i)
    {
        //TODO
        //cout << to_str((candidate->first)[i]);
    }
    cout << endl;
    if (validate(candidate->first))
        notify(candidate);
    else
        delete candidate;
}

bool QAEngine::validate(const NucSequence& sequence) const
{
    //validate the sequence using the QARegions
    mili::CAutonomousIterator<QARegionsCt> rs(regions);
    bool pass(true);
    while (!rs.end() && pass)
    {
        pass = (*rs)->validate(sequence);
        ++rs;
    }
    return pass;
}
