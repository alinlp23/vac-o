/*
 * File:   DevPlugin.cpp
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

#include "vaco-libplugin/libplugin.h"
#include <cassert>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "vaco-rna-backends/IStartProvider.h"
#include "vaco-libplugin/SSValidator.h"
#include "vaco-commons/types.h"

class DevStartProvider : public IStartProvider
{
    NucSequence base;
    virtual void get_complete_start(IFoldInverse* const) {}
    virtual void get_partial_start(IFoldInverse* const backend)
    {
        backend->set_start(base);
    }
public:
    DevStartProvider(NucSequence& s) : base(s) {}
};
/**
 * Plugin for development
 */
class DevPlugin : public IPlugin
{
    NucSequence vacc_sequence;
    NucSequence wt_sequence;
    SecStructure wt_struct;
    SecStructure vacc_struct;
    SecStructure ires;

    Distance min_distance;
    CutOff cutoff;
    Attempts attempts;

    void init_params();
    Parameter<Distance>* min_distance_param;
    Parameter<CutOff>* cutoff_param;

    void init_backends();
    fideo::IFold* fold_backend;
    IFoldInverse* inverse_backend;
    IStructureCmp* struct_cmp_backend;
    ISequenceCmp* seq_cmp_backend;

    void init_comb_regions();
    NucSequencesCt wt_cache;
    ICombinatoryRegion* ssregion;
    ICombinatoryRegion* gcregion;
    CombinatoryRegionsCt regions;

    void init_qa_regions();
    IQAMutator* mutator;
    IQAValidator* validator;
    IQARegion* rnd_ss;

    void init_local_search();
    INeighborhood* neighborhood;
    IStrategy* strategy;

    virtual void get_parameters(ParamsCt& params) const;
    virtual void configure();
    virtual const ISolution* get_initial_solution() const;
    virtual INeighborhood* get_neighborhood() const;
    virtual IStrategy* get_strategy() const;
    virtual void get_qa_regions(QARegionsCt& qaregions) const;
    virtual Score evaluate_solution(const ISolution*);
    virtual RankingSize get_ranking_size() const;
    virtual void unload();
public:
    DevPlugin();
    DevPlugin(const DevPlugin&);
    const DevPlugin& operator=(const DevPlugin&);
};

/**
 * Constructor
 */
DevPlugin::DevPlugin() :
    vacc_sequence("CGCAGGGACTGCAGGTACCCCGCAGGCGCAGATAGAGAC"),
    wt_sequence("CCGCCGCACUUAUCCCUGACGAAUUCUACCAGUCGCGAU"),
    min_distance(0), cutoff(1), attempts(2), min_distance_param(), cutoff_param(),
    fold_backend(), inverse_backend(), struct_cmp_backend(), seq_cmp_backend(),
    wt_cache(), ssregion(), gcregion(), regions(), rnd_ss(), neighborhood(), strategy()
{

    fideo::IFold* p = mili::FactoryRegistry<fideo::IFold, std::string>::new_class("UNAFold");
    assert(p != NULL);
    p->fold(NucSequence("....((((((.......((.....))....))).))).."), false, wt_struct);
    p->fold(NucSequence(".((.(((((.....)).))).))................"), false, vacc_struct);
    p->fold(NucSequence(".((.(((((.....)).))).))."), false, ires);
    //TODO: delete en main?
    delete p;
    init_params();
}

void DevPlugin::configure()
{
    init_backends();
    init_comb_regions();
    init_qa_regions();
    init_local_search();
}

void DevPlugin::get_parameters(ParamsCt& params) const
{
    insert_into(params, min_distance_param);
    insert_into(params, cutoff_param);

}

const ISolution* DevPlugin::get_initial_solution() const
{
    return new Solution(vacc_sequence, regions);
}

INeighborhood* DevPlugin::get_neighborhood() const
{
    return neighborhood;
}

IStrategy* DevPlugin::get_strategy() const
{
    return strategy;
}

void DevPlugin::get_qa_regions(QARegionsCt& qaregions) const
{
    insert_into(qaregions, rnd_ss);
}

Score DevPlugin::evaluate_solution(const ISolution* solution)
{
    Score s;
    NucSequence seq;
    solution->get_sequence(seq);
    s = Score(seq_cmp_backend->compare(seq, wt_sequence));

    return s;
}

RankingSize DevPlugin::get_ranking_size() const
{
    return 5;
}

void DevPlugin::unload()
{
    delete min_distance_param;
    delete cutoff_param;
    delete fold_backend;
    delete inverse_backend;
    delete struct_cmp_backend;
    delete seq_cmp_backend;
    delete ssregion;
    delete gcregion;
    delete neighborhood;
    delete strategy;
    delete mutator;
    delete validator;
    delete rnd_ss;
    delete this;
}

/**
 * Private initializations
 */
void DevPlugin::init_params()
{
    min_distance_param = new Parameter<Distance>("Min distance", min_distance);
    cutoff_param = new Parameter<CutOff>("Threshold cutoff", cutoff);
}

void DevPlugin::init_backends()
{
    fold_backend = mili::FactoryRegistry<fideo::IFold, std::string>::new_class("RNAFold");
    inverse_backend = new INFORNA(ires, 2, 20, 100);
    struct_cmp_backend = new RNAForester;
    seq_cmp_backend = new Hamming;
}

void DevPlugin::init_comb_regions()
{
    /**
     * Fill wt_cache with sequences that fold to wt_struct
     */
    IStartProvider* devprovider = new DevStartProvider(wt_sequence);
    IFoldInverse* wt_inverse = new RNAinverse(wt_struct, 0, 25, 10);
    wt_inverse->query_start(devprovider);
    NucSequence tmp;
    for (size_t i = 0; i < 5; ++i)
    {
        wt_inverse->fold_inverse(tmp);
        insert_into(wt_cache, tmp);
    }
    delete devprovider;
    delete wt_inverse;

    ssregion = new SSRegion(0, 24, wt_struct, vacc_struct, 1, 0.8f, min_distance, wt_cache, false,
                            fold_backend, inverse_backend, struct_cmp_backend,
                            seq_cmp_backend);

    insert_into(regions, ssregion);

    AminoSequence aminoacids;
    string s;
    for (size_t i = 33; i < 39; ++i)
    {
        s += wt_sequence[i].as_char();
    }

    NucSequence seq(s);
    seq.translate(aminoacids);
    gcregion = new GCRegion(33, 39, aminoacids);

    insert_into(regions, gcregion);
}

void DevPlugin::init_qa_regions()
{
    mutator = new RandomMutator(5, 10);
    validator = new SSValidator<MaxSimilitude>(fold_backend, struct_cmp_backend, wt_struct, .5f, false);

    rnd_ss = new QARegion(0, 24, 3, mutator, validator);
}

void DevPlugin::init_local_search()
{
    neighborhood = new Neighborhood(regions, cutoff, attempts);
    strategy = new SimulatedAnnealing(neighborhood, 10, 5, 2, .8f, 3.f, .05f);
    neighborhood->set(strategy);
}

extern "C" IPlugin* create_plugin()
{
    return new DevPlugin();
}
