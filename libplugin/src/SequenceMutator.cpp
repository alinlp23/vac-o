#include "SequenceMutator.h"

SequenceMutator::SequenceMutator(const NucSequence& seq, NMutations max) :
        sequence(seq), mutated(seq), mutations(max), range(), combinator(), positions()
{
    for(SeqIndex i=0; i<sequence.length(); ++i)
    {
        range.push_back(i);
    }
    combinator = new Combinator<list<SeqIndex> >(range, mutations);
    combinator->next(positions);
    reset();
}
SequenceMutator::~SequenceMutator()
{
    delete combinator;
}

void SequenceMutator::update_combinator()
{    
    combinator->update(mutations);
    combinator->next(positions);
}

void SequenceMutator::reset()
{
    for (size_t i = 0; i<positions.size(); ++i)
    {
        SeqIndex pos = positions[i];
        mutated[pos] = Nucleotide((mutated[pos] + 1) % 4);
    }    
}

bool SequenceMutator::next(NucSequence& seq)
{
    bool more;
    if (mutations > 0)
    {
        more = next_mutation(seq);
        if (!more){
            more = true;
            if (!combinator->next(positions))
            {
                --mutations;
                if(mutations > 0)
                    update_combinator();
            }
            mutated = sequence;
            reset();
        }
    }
    else
        more = false;
    return more;
}

bool SequenceMutator::next_mutation(NucSequence& seq)
{    
    seq = mutated;

    SeqIndex pos = positions[positions.size()-1];
    mutated[pos] = Nucleotide((mutated[pos] + 1) % 4);
    if (mutated[pos] == sequence[pos] && mutations > 1)
        reset();
    
    return mutated[positions[0]] != sequence[positions[0]];
}