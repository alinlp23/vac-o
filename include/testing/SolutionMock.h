/* 
 * File:   SolutionMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 13, 2010, 11:12 AM 
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

#ifndef _SOLUTIONMOCK_H
#define	_SOLUTIONMOCK_H

#include <gmock/gmock.h>
#include "ISolution.h"

class SolutionMock : public ISolution
{
public:
    MOCK_METHOD3(update_solution, void(RegionIdx, const NucSequence&, const LocalOptimization&));
    MOCK_CONST_METHOD1(get_sequence, void(NucSequence&));
    MOCK_CONST_METHOD1(compute_local_score, Score(RegionIdx));
    MOCK_CONST_METHOD0(clone, ISolution*());
};


#endif	/* _SOLUTIONMOCK_H */

