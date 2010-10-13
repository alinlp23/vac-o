#include "CombinatoryEngine.h"
#include "IPlugin.h"
#include "IStrategy.h"
#include <iostream>
using std::cout;
using std::endl;

CombinatoryEngine::CombinatoryEngine(IPlugin* const plg) :
plg(plg), strategy(plg->get_strategy())
{
    ISolutionScorer* ssadapter = new PluginScoreAdapter(plg);
    //strategy->set_scorer(ssadapter);
    //strategy->set(this);
}

void CombinatoryEngine::run_forest()
{   
    cout << "Running Combinatory engine..." << endl;
    //strategy->run(plg->get_initial_solution());
}

void CombinatoryEngine::update(const ISolution* solution, Score score)
{
    string seq1 = "AAUAGA";
    NucSequence s1 = seq1;//s->get_sequence(s1)
    Score s = 6; //score
    notify(new SequenceOptimization(s1, s));    
}