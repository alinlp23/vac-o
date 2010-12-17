/*
 * File:   PluginMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 13, 2010, 11:00 AM
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

#ifndef _PLUGINMOCK_H
#define _PLUGINMOCK_H

#include <gmock/gmock.h>
#include "IPlugin.h"
#include "SolutionMock.h"

using ::testing::Return;

class PluginMock : public IPlugin
{
    SolutionMock init_solution;
public:
    PluginMock()
    {
        ON_CALL(*this, get_initial_solution())
        .WillByDefault(Return(&init_solution));
    }
    MOCK_CONST_METHOD1(get_parameters, void(ParamsCt& params));
    MOCK_METHOD0(configure, void());
    MOCK_CONST_METHOD0(get_initial_solution, const ISolution * ());
    MOCK_CONST_METHOD0(get_neighborhood, INeighborhood * ());
    MOCK_CONST_METHOD0(get_strategy, IStrategy * ());
    MOCK_CONST_METHOD1(get_qa_regions, void(QARegionsCt& qaregions));
    MOCK_METHOD1(evaluate_solution, Score(const ISolution*));
    MOCK_CONST_METHOD0(get_ranking_size, RankingSize());
    MOCK_METHOD0(unload, void());
};

#endif  /* _PLUGINMOCK_H */

