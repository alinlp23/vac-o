/*
 * File:   ISequenceCmp.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:26 PM
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

#ifndef _ISEQUENCECMP_H
#define	_ISEQUENCECMP_H

#include <biopp/biopp.h>

#include "rna_backends_types.h"
#include "rna_backends_exceptions.h"

/**
 * Interface for sequence's comparing services.
 */
class ISequenceCmp
{
public:
    /**
     * Compare two sequences.
     * @param seq1 a ARN sequence
     * @param seq2 another ARN sequence
     * @return The distance between sequences.
     */
    virtual Distance compare(const NucSequence&,
                             const NucSequence&) const THROW(RNABackendException) = 0;

    virtual ~ISequenceCmp() {}
};

#endif	/* _ISEQUENCECMP_H */

