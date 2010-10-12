/* 
 * File:   libplugin.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 1, 2010, 12:55 AM 
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

#ifndef _LIBPLUGIN_H
#define	_LIBPLUGIN_H
#include <mili/mili.h>
#include "IPlugin.h"

/*Parameters*/
#include "Parameter.h"

/*Combinatory regions*/
#include "SSRegion.h"
#include "GCRegion.h"

/*libRNA providers*/
#include "RNAFold.h"
#include "RNAFoldInverse.h"
#include "RNAForester.h"
#include "Hamming.h"
/**
 * Plugin for development
 */
class DevPlugin : public IPlugin
{
    static NucSequence sequence;
    static SecStructure wt_struct;
    static SecStructure vacc_struct;
    
    unsigned int counter;
    Distance min_distance;
    CutOff cutoff;

    void init_params();
    Parameter<Distance>* min_distance_param;
    Parameter<CutOff>* cutoff_param;
    
    void init_backends();
    IFold* fold_backend;
    IFoldInverse* inverse_backend;
    IStructureCmp* struct_cmp_backend;
    ISequenceCmp* seq_cmp_backend;

    void init_comb_regions();
    NucSequencesCt wt_cache;
    ICombinatoryRegion* ssregion;
    
    virtual void get_parameters(ParamsCt& params) const;
    virtual const ISolution* get_initial_solution() const;
    virtual INeighborhood* get_neighborhood() const;
    virtual IStrategy* get_strategy() const;
    virtual void get_qa_regions(QARegionsCt& qaregions) const;
    virtual Depth get_qa_depth() const;
    virtual Score evaluate_solution(const ISolution*);
    virtual RankingSize get_ranking_size() const;
    virtual void unload();
public:    
    DevPlugin();
    DevPlugin(const DevPlugin&);
    const DevPlugin& operator=(const DevPlugin&);    
};

#endif	/* _LIBPLUGIN_H */

