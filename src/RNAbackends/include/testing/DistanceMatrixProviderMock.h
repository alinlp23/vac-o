/*
 * File:   DistanceMatrixProviderMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 21, 2010, 5:18 PM
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

#ifndef _DISTANCEMATRIXPROVIDERMOCK_H
#define _DISTANCEMATRIXPROVIDERMOCK_H

#include <gmock/gmock.h>
#include "Hamming.h"

class DistanceMatrixProviderMock : public IDistanceMatrixProvider
{
public:
    MOCK_CONST_METHOD1(get_distance_matrix, void(DistanceMatrix& m));
};

#endif  /* _DISTANCEMATRIXPROVIDERMOCK_H */

