/*
 * File:   IFoldInverse.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:25 PM
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

#ifndef _IFOLDINVERSE_H
#define	_IFOLDINVERSE_H

#include <biopp/biopp.h>
#include "exceptions.h"

/**
 * Interface for sequence's inverse folding services.
 */
class IFoldInverse
{
public:
    /**
     * Make the inverse folding
     * @param sequence the NucSequence to write to.
     */
    virtual void fold_inverse(NucSequence&) throw(RNABackendException) = 0;

    virtual ~IFoldInverse() {}
};

#endif	/* _IFOLDINVERSE_H */

