/*
 * File:   ObserverMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 13, 2010, 3:56 PM
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

#ifndef _OBSERVERMOCK_H
#define _OBSERVERMOCK_H

#include <gmock/gmock.h>
#include "vaco-commons/IObserver.h"

template<class Subject>
class ObserverMock : public IObserver<Subject>
{
public:
    MOCK_METHOD1_T(update, void(const Subject*));
};



#endif  /* _OBSERVERMOCK_H */

