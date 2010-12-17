/*
 * File:   IQAMutator.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 7:20 PM
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

#ifndef _IQAMUTATOR_H
#define _IQAMUTATOR_H

#include <biopp/biopp.h>

/**
 * Interface for sequences mutators used for QA.
 */
class IQAMutator
{
public:
    /**
     * Gets the next mutation.
     * @param seq the sequence to write to the mutation.
     * @return If there are more mutations pending.
     */
    virtual bool next(NucSequence&) = 0;

    /**
     * Sets the base sequence to generate mutants
     * @param seq the sequence.
     */
    virtual void set_base_sequence(const NucSequence&) = 0;

    virtual ~IQAMutator() {}
};

#endif  /* _IQAMUTATOR_H */

