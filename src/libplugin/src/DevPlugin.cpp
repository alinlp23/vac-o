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


#include <cassert>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "fideo/IFoldInverse.h"
#include "fideo/FideoStructureParser.h"
#include "vaco-libplugin/libplugin.h"
#include "vaco-libplugin/SSValidator.h"
#include "vaco-libplugin/QAWholeRegion.h"
#include "vaco-libplugin/RecombValidator.h"
#include "vaco-commons/types.h"
#include "vaco-commons/RecombinantInfo.h"

class DevStartProvider : public fideo::IStartProvider
{
    NucSequence base;
    virtual void get_complete_start(fideo::IFoldInverse* const) {}
    virtual void get_partial_start(fideo::IFoldInverse* const backend)
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

    fideo::Distance min_distance;
    CutOff cutoff;
    Attempts attempts;

    //Gets sequences and regions to recombine with solutions
    void getRecombinantInfo(RecombinantInfo& recomb);

    void initQaRecombinant();
    RecombinantInfo* recombinantInfo;
    IQARegion* iQARecomb;

    void init_params();
    Parameter<fideo::Distance>* min_distance_param;
    Parameter<CutOff>* cutoff_param;

    void init_backends();
    fideo::IFold* fold_backend;
    fideo::IFoldInverse* inverse_backend;
    fideo::IStructureCmp* struct_cmp_backend;
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

    fideo::ViennaParser::parseStructure(std::string("....((((((.......((.....))....))).))).."), wt_struct);
    fideo::ViennaParser::parseStructure(std::string(".((.(((((.....)).))).))................"), vacc_struct);
    fideo::ViennaParser::parseStructure(std::string(".((.(((((.....)).))).))."), ires);

    init_params();
}

void DevPlugin::configure()
{
    init_backends();
    init_comb_regions();
    initQaRecombinant();
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
    insert_into(qaregions, iQARecomb);
}

Score DevPlugin::evaluate_solution(const ISolution* solution)
{
    NucSequence seq;
    solution->get_sequence(seq);
    const Score s = Score(seq_cmp_backend->compare(seq, wt_sequence));

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
    delete iQARecomb;
    delete recombinantInfo;
    delete this;
}

/**
 * Private initializations
 */
void DevPlugin::init_params()
{
    min_distance_param = new Parameter<fideo::Distance>("Min distance", min_distance);
    cutoff_param = new Parameter<CutOff>("Threshold cutoff", cutoff);
}

void DevPlugin::init_backends()
{
    fold_backend = fideo::Folder::new_class("RNAFold");
    inverse_backend = fideo::IFoldInverse::factory("INFORNA", fideo::InverseFoldParams(ires, 2, 20, 100));
    struct_cmp_backend = fideo::IStructureCmp::Factory::new_class("RNAForester");
    seq_cmp_backend = new Hamming;
}

void DevPlugin::init_comb_regions()
{
    /**
     * Fill wt_cache with sequences that fold to wt_struct
     */
    fideo::IStartProvider* const devprovider = new DevStartProvider(wt_sequence);
    fideo::IFoldInverse* const wt_inverse = fideo::IFoldInverse::factory("INFORNA"/*"RNAinverse"*/, fideo::InverseFoldParams(wt_struct, 0, 25, 10));

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

void DevPlugin::initQaRecombinant()
{
    const fideo::Similitude similitude = .5f;
    recombinantInfo = new RecombinantInfo();
    getRecombinantInfo(*recombinantInfo);
    IQAValidator* validator = new RecombValidator<MaxSimilitude>(*recombinantInfo, *fold_backend, *struct_cmp_backend, similitude);
    iQARecomb = new QAWholeRegion(validator);
}

void DevPlugin::init_local_search()
{
    neighborhood = new Neighborhood(regions, cutoff, attempts);
    strategy = new SimulatedAnnealing(neighborhood, 10, 5, 2, .8f, 3.f, .05f);
    neighborhood->set(strategy);
}

void DevPlugin::getRecombinantInfo(RecombinantInfo& recomb)
{
    RecombinantInfo::RecombinantSequenceInfo recombinantSequenceInfo;
    recomb.recombinantSequences.push_back(recombinantSequenceInfo);
    recombinantSequenceInfo.sequence = NucSequence("ACATTTACT");

    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(1,3));
    recombinantSequenceInfo.regions.push_back(RecombinantInfo::PositionsRange(5,7));
}

extern "C" IPlugin* create_plugin()
{
    return new DevPlugin();
}
