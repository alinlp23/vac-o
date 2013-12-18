/*
 * File:   AllMutator.cpp
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

#include "vaco-libplugin/AllMutator.h"

AllMutator::AllMutator(size_t l, NMutations m) : mutator(l, m), mutations(m)
{}

bool AllMutator::next(NucSequence& seq)
{
    return mutator.next(seq);
}

void AllMutator::set_base_sequence(const NucSequence& seq)
{
    mutator.begin(seq);
}

