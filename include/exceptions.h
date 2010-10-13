/* 
 * File:   exceptions.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 30, 2010, 11:48 PM 
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

#ifndef _EXCEPTIONS_H
#define	_EXCEPTIONS_H

#include <string>
#include <exception>
using std::exception;
using std::string;

class Exception : public exception
{
    const string message;
public:
    explicit Exception(const string& msg): message(msg)
    {}
    virtual const char* what() const throw(){
        return message.c_str();
    }

    ~Exception() throw() {};
};

class RNABackendException : public Exception
{
public:
    RNABackendException(const string& msg) : Exception("libRNA says: \n\t"+msg)
    {}
};

class PluginException : public Exception
{
public:
    PluginException(const string& msg) :  Exception("PluginAdmin says: \n\t"+msg)
    {}
};


#endif	/* _EXCEPTIONS_H */

