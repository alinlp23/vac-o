/*
 * File:   QAMutatorMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 16, 2010, 6:22 PM
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

#ifndef _QAMUTATORMOCK_H
#define _QAMUTATORMOCK_H

#include <gmock/gmock.h>
#include "IQAMutator.h"

class QAMutatorMock : public IQAMutator
{
public:
    MOCK_METHOD1(next, bool(NucSequence&));
    MOCK_METHOD1(set_base_sequence, void(const NucSequence&));
};



#endif  /* _QAMUTATORMOCK_H */

