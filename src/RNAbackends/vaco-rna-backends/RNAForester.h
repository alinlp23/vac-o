/*
 * File:   RNAForester.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 1, 2010, 7:00 PM
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

#ifndef _RNAFORESTER_H
#define _RNAFORESTER_H

#include <string>
#include "vaco-rna-backends/IStructureCmp.h"
/**
 * Implementation using system call to RNAforester
 */
class RNAForester : public IStructureCmp
{
    static const FilePath IN;
    static const FilePath OUT;
    static const FileLineNo LINE_NO;
    static const std::string RNAforester_PROG;
    virtual fideo::Similitude compare(const biopp::SecStructure&, const biopp::SecStructure&) const;
};

#endif  /* _RNAFORESTER_H */

