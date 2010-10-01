/* 
 * File:   CombinatoryEngine.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:08 PM 
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

#ifndef _COMBINATORYENGINE_H
#define	_COMBINATORYENGINE_H

#include "biopp.h"
#include "types.h"

#include "ISubject.h"
#include "ICombinatoryRegion.h"
#include "IPlugin.h"


class CombinatoryEngine : public ISubject<NucSequence>
{    
    NucSequence sequence;
    CutOff cutoff;
    CombinatoryRegionsCt regions;
    const IPlugin* const plg;
public:
    /**
     * Constructor will ask the plugin for needed data.
     * @param pointer to IPlugin
     */
    CombinatoryEngine(const IPlugin*);

    CombinatoryEngine(const CombinatoryEngine&);
    CombinatoryEngine& operator=(const CombinatoryEngine&);

    /**
     * Run the engine until plg->done().
     * Will notify the observers for each sequence found.
     */
    void run();
};

#endif	/* _COMBINATORYENGINE_H */

