#include "SequenceRanker.h"

#include <iostream>
using std::cout;
using std::endl;

SequenceRanker::SequenceRanker(RankingSize size) :
Ranker<const SequenceOptimization*, AddAfterEqual, SequenceOptimizationCmp,
       DisposalDeletePolicy<const SequenceOptimization*> >::Ranker(size)
{}

void SequenceRanker::update(const SequenceOptimization* opt)
{
    NucSequence seq;
    seq = opt->first;
    cout << "Ranking optimization: " << seq << endl;
    insert(opt);
}
