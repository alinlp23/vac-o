/*
 * File:   FoldMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 15, 2010, 8:51 PM
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

#ifndef _FOLDMOCK_H
#define _FOLDMOCK_H

#include <gmock/gmock.h>
#include "fideo/IFold.h"

class FoldMock : public fideo::IFold
{
public:
    MOCK_METHOD3(fold, fideo::Fe(const biopp::NucSequence&, const bool, biopp::SecStructure&));
    MOCK_METHOD4(fold, fideo::Fe(const biopp::NucSequence&, const bool, biopp::SecStructure&, fideo::IMotifObserver*));


    MOCK_METHOD4(foldTo,void(const biopp::NucSequence&, const bool, biopp::SecStructure&, const fideo::FilePath&));
    MOCK_METHOD5(foldTo,void(const biopp::NucSequence&, const bool, biopp::SecStructure&, const fideo::FilePath&, fideo::IMotifObserver*));

    MOCK_METHOD2(foldFrom,fideo::Fe(const fideo::FilePath&, biopp::SecStructure&));
    MOCK_METHOD3(foldFrom,fideo::Fe(const fideo::FilePath&, biopp::SecStructure&, fideo::IMotifObserver*));
};

#endif  /* _FOLDMOCK_H */