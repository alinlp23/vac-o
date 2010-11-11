/*
 * File:   RNAForester.cpp
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 10, 2010, 4:26 PM
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

#include "RNAForester.h"

const FilePath RNAForester::IN = "forester.in";
const FilePath RNAForester::OUT = "forester.out";
const Command RNAForester::CMD = "RNAforester -r --score -f "+ RNAForester::IN +" > "+RNAForester::OUT;
const FileLineNo RNAForester::LINE_NO = 1;

Similitude RNAForester::compare(const SecStructure& struct1,
                                const SecStructure& struct2) const throw(RNABackendException)
{    
    FileLinesCt lines;
    insert_into(lines, struct1.to_str());
    insert_into(lines, struct2.to_str());

    write(IN, lines);
    exec(CMD);

    FileLine aux;
    read_line(OUT, LINE_NO, aux);

    Similitude s;
    read_value(aux, s);
    return s;
}
