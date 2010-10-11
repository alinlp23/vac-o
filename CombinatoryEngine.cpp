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
    string seq1 = "AAUAGA";
    NucSequence s1 = seq1;
    notify(new SequenceOptimization(s1, 6));
    string seq2 = "AAUAGU";
    NucSequence s2 = seq2;
    notify(new SequenceOptimization(s2, 9));
    string seq3 = "GGUAGU";
    NucSequence s3 = seq3;
    notify(new SequenceOptimization(s3, 5));
}

bool CombinatoryEngine::update(const ISolution* s)
{
    NucSequence seq;
    //s->get_sequence(seq);
    float score = plg->evaluate_sequence(seq);
    return strategy->update_neighbors(s,score);
}