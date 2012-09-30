/*
 * File:   IStructureCmp.h
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

#ifndef _ISTRUCTURECMP_H
#define _ISTRUCTURECMP_H

#include <biopp/biopp.h>
#include "fideo/rna_backends_types.h"
#include "fideo/rna_backends_exceptions.h"

/**
 * Interface for structure's comparing services.
 */
class IStructureCmp
{
public:
    /**
     * Compare two structures.
     * @param struct1 a secondary structure.
     * @param struct2 another secondary structure.
     * @return The similitude between structures.
     */
    virtual Similitude compare(const SecStructure& struct1,
                               const SecStructure& struct2) const THROW((RNABackendException)) = 0;

    virtual ~IStructureCmp() {}
};

#endif  /* _ISTRUCTURECMP_H */
