#include "SequenceOptimization.h"

bool SequenceOptimizationCmp::operator()(const SequenceOptimization* opt1,
        const SequenceOptimization* opt2) const
{
    return opt1->second > opt2->second;
}
