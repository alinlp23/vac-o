/*
 * File:   QAWholeRegion.h
 * Author: Facundo Munoz <facuu.munoz at gmail.com>
 *
 *
 * Copyright (C) 2010  Facundo Munoz, FuDePAN
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

#ifndef QAWHOLEREGION_H
#define QAWHOLEREGION_H

#include <biopp/biopp.h>
#include "fideo/RnaBackendsTypes.h"
#include "vaco-commons/types.h"
#include "vaco-commons/IQARegion.h"

class IQAValidator;

class QAWholeRegion : public IQARegion
{
    virtual bool validate(const NucSequence& nuc) const {
        const bool pass = validator->validate(nuc);   
        return pass;    
    }
    const IQAValidator* validator;
public:
    QAWholeRegion(const IQAValidator* validator)
      : validator(validator)
    {};
};

#endif