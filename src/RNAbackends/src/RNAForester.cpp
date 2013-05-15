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

#include <sstream>

#include "vaco-rna-backends/RNAForester.h"
#include "fideo/FideoHelper.h"

using std::stringstream;

const FilePath RNAForester::IN = "forester.in";
const FilePath RNAForester::OUT = "forester.out";
const FileLineNo RNAForester::LINE_NO = 1;
const std::string RNAForester::RNAforester_PROG = "";//TODO: ??

Similitude RNAForester::compare(const biopp::SecStructure& struct1, const biopp::SecStructure& struct2) const throw(RNABackendException)
{
    stringstream ss;
    ss << RNAforester_PROG << " -r --score -f "
       << IN << " > " << OUT;

    const fideo::Command CMD = ss.str();

    FileLinesCt lines;
    string struct1_str;
    string struct2_str;
    struct1.to_str(struct1_str);
    struct2.to_str(struct2_str);

    insert_into(lines, struct1_str);
    insert_into(lines, struct2_str);

    fideo::helper::write(IN, lines);
    fideo::helper::runCommand(CMD);

    FileLine aux;
    fideo::helper::readLine(OUT, LINE_NO, aux);

    Similitude s;
    fideo::helper::readValue(aux, s);
    return s;
}
