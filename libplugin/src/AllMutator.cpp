#include "AllMutator.h"
#include "SequenceMutator.h"

AllMutator::AllMutator(NMutations m) : mutator(), mutations(m)
{}

AllMutator::~AllMutator()
{
    delete mutator;
}

bool AllMutator::next(NucSequence& seq)
{
    return mutator->next(seq);
}

void AllMutator::set_base_sequence(const NucSequence& seq)
{
    delete mutator;
    mutator = new SequenceMutator(seq, mutations);
}

