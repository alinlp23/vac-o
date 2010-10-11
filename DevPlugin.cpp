#include "libplugin.h"

/**
 * Static memebers
 */
string seq = "CGCAGGGAUCGCAGGUACCCCGCAGGCGCAGAUACCCUA";
NucSequence DevPlugin::sequence = seq;
SecStructure DevPlugin::vacc_struct = "...(((((((....(..((.....))..).))).)))).";
SecStructure DevPlugin::wt_struct = "....((((((.......((.....))....))).)))..";

/**
 * Constructor
 */
DevPlugin::DevPlugin() :
counter(0), min_distance(0), cutoff(1), min_distance_param(), cutoff_param(),
fold_backend(), inverse_backend(), struct_cmp_backend(), seq_cmp_backend(),
wt_cache(), ssregion()
{    
    init_params();
    init_backends();
    init_comb_regions();
}

void DevPlugin::get_parameters(ParamsCt& params) const
{
    insert_into(params, min_distance_param);
    insert_into(params, cutoff_param);

}

void DevPlugin::get_sequence(NucSequence& seq) const
{
    seq = sequence;
}

void DevPlugin::get_combinatory_regions(CombinatoryRegionsCt& cregions) const
{            
    insert_into(cregions, ssregion);
}

void DevPlugin::get_qa_regions(QARegionsCt& qaregions) const
{}

CutOff DevPlugin::get_comb_cutoff() const
{
    return cutoff;
}

Depth DevPlugin::get_qa_depth() const
{
    return 5;
}

bool DevPlugin::done() const
{
    return counter==10;
}

Score DevPlugin::evaluate_sequence(const NucSequence& sequence)
{
    ++counter;    
    return counter;
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
    fold_backend = new RNAFold;    
    inverse_backend = new RNAFoldInverse(sequence, vacc_struct);
    struct_cmp_backend = new RNAForester;
    seq_cmp_backend = new Hamming;
}

void DevPlugin::init_comb_regions()
{
    /**
     * Fill wt_cache with sequence that fold to wt_struct
     */
    ssregion = new SSRegion(0, 10, wt_struct, vacc_struct, 1, 0.9f, 10, wt_cache, 
                            fold_backend, inverse_backend, struct_cmp_backend,
                            seq_cmp_backend);
}