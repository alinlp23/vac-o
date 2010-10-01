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

/**
 * Interface for user's defined plugins
 */
class IPlugin
{
public:
    /**
     * Gets the required parameters by the plugin.
     * @param params container of IParameter to write to.
     */
    virtual void get_parameters(ParamsCt& params) const = 0;
    /**
     * Gets the initial ARN sequence.
     * @param seq NucSecuence to write to.
     */
    virtual void get_sequence(NucSequence& seq) const = 0;
    /**
     * Gets the combinatory regions to be used by the combinatory engine.
     * @param cregions container of ICombinatoryRegion to write to.
     */
    virtual void get_combinatory_regions(CombinatoryRegionsCt& cregions) const = 0;
    /**
     * Gets the QA regions to be used by the QA engine.
     * @param qaregions list of IQARegion to write to.
     */
    virtual void get_qa_regions(QARegionsCt& qaregions) const = 0;
    /**
     * Gets the threshold cutoff used by the combinatory engine.
     * @return A floating point between 0 and 1.
     */
    virtual CutOff get_cutoff() const = 0;
    /**
     * Decides when to stop computing.
     * @return Stop or not.
     */
    virtual bool done() const = 0;
    /**
     * Evaluate a given ARN sequence.
     * @param sequence the ARN sequence to evaluate.
     * @return The score assigned.
     */
    virtual Score evaluate_sequence(const NucSequence& sequence) = 0;
    /**
     * Unload the plugin.
     */
    virtual void unload() = 0;

    virtual ~IPlugin(){}
};

#endif	/* _IPLUGIN_H */

