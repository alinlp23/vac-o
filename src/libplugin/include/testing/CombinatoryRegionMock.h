/*
 * File:   CombinatoryRegionMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 19, 2010, 5:03 PM
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

#ifndef _COMBINATORYREGIONMOCK_H
#define _COMBINATORYREGIONMOCK_H

#include <gmock/gmock.h>
#include "CombinatoryRegion.h"

class CombinatoryRegionMock : public CombinatoryRegion
{
public:
    CombinatoryRegionMock() : CombinatoryRegion(0, 0) {}
    MOCK_CONST_METHOD1(evaluate, Score(const NucSequence&));
    MOCK_METHOD2(generate, Score(NucSequence&, NucSequence&));
    MOCK_METHOD1(set_base_sequence, void(const NucSequence&));

    void set_bounds(SeqIndex s, SeqIndex e)
    {
        start = s;
        end = e;
    }
};

#endif  /* _COMBINATORYREGIONMOCK_H */

