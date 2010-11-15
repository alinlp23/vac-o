/* 
 * File:   StrategyMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 13, 2010, 11:14 AM 
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

#ifndef _STRATEGYMOCK_H
#define	_STRATEGYMOCK_H

#include <gmock/gmock.h>
#include "IStrategy.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::DoAll;

class SolutionScorerMock : public ISolutionScorer
{
public:
    MOCK_CONST_METHOD1(evaluate, Score(const ISolution*));
};

class SolutionObserverMock : public ISolutionObserver
{
public:
    MOCK_METHOD2(update, void(const ISolution* const, Score));
};

class StrategyMock : public IStrategy
{    
public:
    void assign_scorer(const ISolutionScorer* s)
    {
        scorer = s;
    }
    const ISolutionScorer* scorer;
    StrategyMock()
    {
        ON_CALL(*this, set_scorer(_)).WillByDefault(DoAll(Invoke(this, &StrategyMock::assign_scorer), Return()));
    }
    MOCK_METHOD2(run, void(const ISolution*, ISolutionObserver*));
    MOCK_METHOD1(set_scorer, void(const ISolutionScorer*));
    MOCK_METHOD1(update, bool(const ISolution*));
};


#endif	/* _STRATEGYMOCK_H */

