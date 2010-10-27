/* 
 * File:   RNABackendProxy.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 26, 2010, 4:31 PM 
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

#ifndef _RNABACKENDPROXY_H
#define	_RNABACKENDPROXY_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <mili/mili.h>

#include "types.h"
#include "exceptions.h"

using std::string;

typedef string FileLine;
typedef string Command;
typedef unsigned int FileLineNo;
typedef std::list<string> FileLinesCt;

/**
 * Execute a give command using a system call
 * @param cmd the RNA backend command
 */
inline void exec(const Command& cmd) throw(RNABackendException)
{
    int status = system(cmd.c_str());
    if (status)
        throw RNABackendException("An error ocurred trying to execute: "+cmd);
}

/**
 * Write a file with multiple lines.
 * @param file the file path
 * @param lines the lines to write
 */
inline void write(const Path& file, FileLinesCt& lines) throw(RNABackendException)
{
    std::ofstream out;
    out.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    try{
        out.open(file.c_str());
        CAutonomousIterator<FileLinesCt> it(lines);
        while (!it.end())
        {
            out << *it << std::endl;
            ++it;
        }
    }
    catch (std::ifstream::failure e)
    {
        throw RNABackendException("An error ocurred trying to write "+file);
    }
    out.close();
}

/**
 * Write a file with a single line.
 * @param file the file path
 * @param line the line to write
 */
inline void write(const Path& file, FileLine& line) throw(RNABackendException)
{
    std::ofstream out;
    out.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        out.open(file.c_str());
        out << line << std::endl;        
    }
    catch (std::ifstream::failure e)
    {
        throw RNABackendException("An error ocurred trying to write "+file);
    }
    out.close();
}

/**
 * Read a line from a file
 * @param file the file path
 * @param lineno the line number to read
 * @param line where to write the read line
 */
inline void read_line(const Path& file, FileLineNo lineno, FileLine& line) throw(RNABackendException)
{
    std::ifstream in;
    in.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        in.open(file.c_str());
        if (lineno > 0)
        {
            string aux;
            for (size_t i=0; i<lineno; ++i)
            {
                getline(in, aux);
            }
        }
        getline(in, line);
    }
    catch (std::ifstream::failure e)
    {
        throw RNABackendException("An error ocurred trying to read "+file);
    }
    in.close();
}

/**
 * Read a value from a file line using offset and length
 * @param line the file line
 * @param offset the offset in the line
 * @param n the length to read
 * @param t where to write the value.
 */
template<class T>
inline void read_value(const FileLine& line, FileLine::size_type offset, size_t n, T& t) throw(RNABackendException)
{
    bool success = from_string(line.substr(offset, n), t);
    if (!success)
        throw RNABackendException("Could not read the value from given line, offset and length");
}

/**
 * Read a value from a line file.
 * @param line the file line
 * @param t where to write the value
 */
template<class T>
inline void read_value(const FileLine& line, T& t) throw(RNABackendException)
{
    bool success = from_string(line, t);
    if (!success)
        throw RNABackendException("Could not read the value from given line");
}

struct StringNotFound : std::exception{};

/**
 * Ensure that a given position it's different than string::npos
 * @param found the position to compare
 * @return the position given if it's different than string::npos or throw StringNotFound
 */
inline string::size_type ensure_found(string::size_type found) throw(StringNotFound)
{    
    if (found != string::npos)
        return found;
    else
        throw StringNotFound();
}

/**
 * Ensure that a given position it's different than string::npos
 * @param found the position to compare
 * @param default_value the value to return in case of string::npos
 * @return found or default
 */
inline string::size_type ensure_found(string::size_type found, string::size_type default_value)
{ 
    if (found != string::npos)
        return found;
    else
        return default_value;
}

#endif	/* _RNABACKENDPROXY_H */

