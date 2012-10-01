/*
 * File:   Parameter.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 1, 2010, 8:51 PM
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

#ifndef _PARAMETER_H
#define _PARAMETER_H

#include <mili/mili.h>
#include "vaco-commons/IParameter.h"

template<class Type>
class Parameter : public IParameter
{
    const string name;
    Type& value;

public:
    Parameter(const string&, Type&);
    Parameter(const Parameter&);
    Parameter& operator=(const Parameter&);

    virtual bool set_value(const string&);
    virtual void get_name(string& name) const;
};

/*
 * Implementation
 * Why if this goes to a cpp it doesn't link?
 */
template<class Type>
Parameter<Type>::Parameter(const string& name, Type& value) :
    name(name), value(value)
{}

template<class Type>
void Parameter<Type>::get_name(string& name) const
{
    name = this->name;
}

template<class Type>
bool Parameter<Type>::set_value(const string& value)
{
    return mili::from_string(value, this->value);
}

#endif  /* _PARAMETER_H */

