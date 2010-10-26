#include "libplugin.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "IStartProvider.h"

class DevStartProvider : public IStartProvider
{
    NucSequence base;
    virtual void get_complete_start(IFoldInverse* const){}
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
    static NucSequence vacc_sequence;
    static NucSequence wt_sequence;
    static SecStructure wt_struct;
    static SecStructure vacc_struct;
    static SecStructure ires;

    Distance min_distance;
    CutOff cutoff;
    Attempts attempts;

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
    CombinatoryRegionsCt regions;

    void init_local_search();
    INeighborhood* neighborhood;
    IStrategy* strategy;

    virtual void get_parameters(ParamsCt& params) const;
    virtual void configure();
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

/**
 * Static memebers
 */
string seq = "CGCAGGGAUCGCAGGUACCCCGCAGGCGCAGAUACCCUA";
string wt_seq = "CCGCCGCACUUAUCCCUGACGAAUUCUACCAGUCGCGAU";
NucSequence DevPlugin::vacc_sequence = seq;
NucSequence DevPlugin::wt_sequence = wt_seq;                        
SecStructure DevPlugin::vacc_struct = "...(((((((....(..((.....))..).))).)))).";
SecStructure DevPlugin::ires = "(..((.....))..)";
SecStructure DevPlugin::wt_struct = "....((((((.......((.....))....))).)))..";

/**
 * Constructor
 */
DevPlugin::DevPlugin() :
        min_distance(0), cutoff(1), attempts(2), min_distance_param(), cutoff_param(),
        fold_backend(), inverse_backend(), struct_cmp_backend(), seq_cmp_backend(),
        wt_cache(), ssregion(), regions(), neighborhood(), strategy()
{
    init_params();    
}

void DevPlugin::configure()
{
    init_backends();
    init_comb_regions();
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
{}

Depth DevPlugin::get_qa_depth() const
{
    return 5;
}

Score DevPlugin::evaluate_solution(const ISolution* solution)
{
    Score s;
    cout << "Solution score:" << endl;
    cin >> s;
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
    delete neighborhood;
    delete strategy;
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
    inverse_backend = new RNAinverse(ires, 0, 10, 100);
    struct_cmp_backend = new RNAForester;
    seq_cmp_backend = new Hamming;    
}

void DevPlugin::init_comb_regions()
{
    /**
     * Fill wt_cache with sequences that fold to wt_struct
     */
    IStartProvider* devprovider = new DevStartProvider(wt_sequence);
    IFoldInverse* wt_inverse = new RNAinverse(wt_struct, 0, 10, 100);
    wt_inverse->query_start(devprovider);
    NucSequence tmp;
    for (size_t i=0; i<20; ++i)
    {
        wt_inverse->fold_inverse(tmp);
        insert_into(wt_cache, tmp);        
    }

    ssregion = new SSRegion(14, 29, wt_struct, vacc_struct, 1, 0.9f, 10, wt_cache,
                            fold_backend, inverse_backend, struct_cmp_backend,
                            seq_cmp_backend);

    insert_into(regions, ssregion);
    
    delete devprovider;
    delete wt_inverse;
}

void DevPlugin::init_local_search()
{
    neighborhood = new Neighborhood(regions, cutoff, attempts);
    strategy = new FirstImprovement(neighborhood, 3, 1);
    neighborhood->set(strategy);
}

extern "C" IPlugin* create_plugin()
{
    return new DevPlugin();
}
