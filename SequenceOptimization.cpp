#include "SequenceOptimization.h"

SequenceOptimization::SequenceOptimization(const NucSequence& seq, Score score):
sequence(seq), score(score)
{}

Score SequenceOptimization::get_score() const
{
    return score;
}

void SequenceOptimization::get_sequence(NucSequence& seq) const
{
    seq = sequence;
}

bool SequenceOptimizationCmp::operator()(const SequenceOptimization* opt1,
                                         const SequenceOptimization* opt2) const
{
    return opt1->get_score() > opt2->get_score();
}
