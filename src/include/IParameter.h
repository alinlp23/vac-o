/*
 * File:   IParameter.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 4:53 PM
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

#ifndef _IPARAMETER_H
#define	_IPARAMETER_H

#include <list>
#include <string>
using std::list;
using std::string;
/**
 * Interface for plugin's parameters
 */
class IParameter
{
public:
    /**
     * Sets the parameter's values.
     * @param value the value in string format.
     * @return If it was possible to set the value or not.
     */
    virtual bool set_value(const string& value) = 0;
    /**
     * Gets the name of the parameter.
     * @return The parameter's name.
     */
    virtual void get_name(string& name) const = 0;

    virtual ~IParameter() {}
};

/**
 * Container of IParameter
 */
typedef list<IParameter*> ParamsCt;

#endif	/* _IPARAMETER_H */

