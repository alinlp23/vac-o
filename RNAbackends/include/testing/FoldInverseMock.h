/* 
 * File:   FoldInverseMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 15, 2010, 8:52 PM 
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

#ifndef _FOLDINVERSEMOCK_H
#define	_FOLDINVERSEMOCK_H

#include <gmock/gmock.h>
#include "IFoldInverse.h"

class FoldInverseMock : public IFoldInverse
{
public:
    MOCK_METHOD1(fold_inverse, void(NucSequence&));
    MOCK_METHOD1(set_start, void(const NucSequence&));
    MOCK_METHOD1(query_start, void(IStartProvider*));
};


#endif	/* _FOLDINVERSEMOCK_H */

