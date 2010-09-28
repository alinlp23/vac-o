/* 
 * File:   IPlugin.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 4:44 PM 
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

#ifndef _IPLUGIN_H
#define	_IPLUGIN_H
#include <list>
#include "ICombinatoryRegion.h"
#include "IQARegion.h"
#include "IParameter.h"

using std::list;

class IPlugin
{
public:
    virtual list<IParameter> get_parameters() const = 0;
    virtual NucSequence* get_sequence() const = 0;
    virtual list<ICombinatoryRegion>* get_combinatory_regions() const = 0;
    virtual list<IQARegion>* get_qa_regions() const = 0;
    virtual CutOff get_cutoff() const = 0;
    virtual bool done() const = 0;
    virtual Score evaluate_sequence(const NucSequence& sequence) = 0;
    virtual void unload() = 0;

    virtual ~IPlugin(){}
};

#endif	/* _IPLUGIN_H */

