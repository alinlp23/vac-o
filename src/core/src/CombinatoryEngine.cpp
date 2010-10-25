#include "CombinatoryEngine.h"
#include "IStrategy.h"

#include <iostream>
using std::cout;
using std::endl;

CombinatoryEngine::CombinatoryEngine(IPlugin* const plg) :
        plg(plg), strategy(plg->get_strategy()), ssadapter()
{
    ssadapter = new PluginScoreAdapter(plg);
    strategy->set_scorer(ssadapter);
}

void CombinatoryEngine::run_forest()
{
    cout << "Running Combinatory engine..." << endl;
    strategy->run(plg->get_initial_solution(), this);
}

void CombinatoryEngine::update(const ISolution* const solution, Score score)
{
    NucSequence sequence;
    solution->get_sequence(sequence);    
    notify(new SequenceOptimization(sequence, score));
}

CombinatoryEngine::~CombinatoryEngine()
{
    delete ssadapter;
}
