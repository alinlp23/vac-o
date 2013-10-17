/*
 * File:   QARegion.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 3:51 PM
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

#ifndef _QAREGION_H
#define _QAREGION_H

#include <queue>
#include "fideo/RnaBackendsTypes.h"
#include "vaco-commons/types.h"
#include "vaco-commons/IQARegion.h"

using std::queue;
using biopp::SeqIndex;

class IQAMutator;
class IQAValidator;

class QARegion : public IQARegion
{
    const SeqIndex start;
    const SeqIndex end;
    const Depth depth;

    IQAMutator* const mutator;
    const IQAValidator* const validator;

    virtual bool validate(const NucSequence&) const;
    bool validate_level(const NucSequence&, queue<NucSequence>&) const;
    bool validate_mutants(const NucSequence&, const NucSequence&, queue<NucSequence>&) const;
public:
    QARegion(SeqIndex, SeqIndex, Depth, IQAMutator*, const IQAValidator*);
    virtual ~QARegion() {}
};

#endif  /* _QAREGION_H */

