#include "SequenceEvaluator.h"
#include "IPlugin.h"
#include <iostream>
using std::cout;
using std::endl;
SequenceEvaluator::SequenceEvaluator(IPlugin* const plg):
plg(plg)
{}

void SequenceEvaluator::update(const NucSequence* seq)
{
    cout << "Evaluating " << *seq << endl;
    Score score = plg->evaluate_sequence(*seq);
    SequenceOptimization* opt = new SequenceOptimization(*seq, score);
    notify(opt);
}
