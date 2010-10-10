#include "CombinatoryEngine.h"
#include "IPlugin.h"
#include "IStrategy.h"
#include <iostream>
using std::cout;
using std::endl;

CombinatoryEngine::CombinatoryEngine(const NucSequence& seq, const CombinatoryRegionsCt& rs,
                                     CutOff c, IPlugin* const plg) :
sequence(seq), cutoff(c), regions(rs), plg(plg), neighborhood(), strategy()
{}

void CombinatoryEngine::run()
{    
    /*
     * while(!plg->done())
     * {
     *     get a new sequence s
     *     notify(s);
     * }
     *
     */
    cout << "Running Combinatory engine..." << endl;
    NucSequence s1 = "AAUAGA";
    notify(new SequenceOptimization(s1, 6));
    NucSequence s2 = "AAUAGU";
    notify(new SequenceOptimization(s2, 9));
    NucSequence s3 = "GGUAGU";
    notify(new SequenceOptimization(s3, 5));
}

bool CombinatoryEngine::update(const Solution* s)
{
    NucSequence seq;
    //s->get_sequence(seq);
    float score = plg->evaluate_sequence(seq);
    return strategy->update_neighbors(s,score);
}