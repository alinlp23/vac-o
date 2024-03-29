/*
 * File:   StructureCmpMock.h
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

#ifndef _STRUCTURECMPMOCK_H
#define _STRUCTURECMPMOCK_H

#include <gmock/gmock.h>
#include "fideo/IStructureCmp.h"

class StructureCmpMock : public fideo::IStructureCmp
{
public:
    MOCK_CONST_METHOD2(compare, fideo::Similitude(const biopp::SecStructure&, const biopp::SecStructure&));
};

#endif  /* _STRUCTURECMPMOCK_H */

