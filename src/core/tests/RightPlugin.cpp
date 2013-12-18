#include "vaco-commons/IPlugin.h"

class RightPlugin : public IPlugin
{
    virtual void get_parameters(ParamsCt& /*params*/) const
    {}
    virtual void configure()
    {}
    virtual const ISolution* get_initial_solution() const
    {
        return NULL;
    }
    virtual INeighborhood* get_neighborhood() const
    {
        return NULL;
    }
    virtual IStrategy* get_strategy() const
    {
        return NULL;
    }
    virtual void get_qa_regions(QARegionsCt& /*qaregions*/) const
    {}
    virtual Score evaluate_solution(const ISolution*)
    {
        return 0;
    }
    virtual RankingSize get_ranking_size() const
    {
        return 0;
    }
    virtual void unload()
    {
        delete this;
    }
};

extern "C" IPlugin* create_plugin()
{
    return new RightPlugin;
}
