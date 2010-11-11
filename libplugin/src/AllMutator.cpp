#include "AllMutator.h"

AllMutator::AllMutator(size_t l, NMutations m) : mutator(l, m), mutations(m)
{}

bool AllMutator::next(NucSequence& seq)
{
    return mutator.next(seq);
}

void AllMutator::set_base_sequence(const NucSequence& seq)
{
    mutator.begin(seq);
}

