#include "Hamming.h"
#include <mili/mili.h>

Distance Hamming::compare(const NucSequence& seq1,
                          const NucSequence& seq2) const throw(RNABackendException)
{
    /*This could be optional*/
    if(seq1.size() != seq2.size())
        throw RNABackendException("Hamming distance must be calculated over sequences of the same size");

    Distance h=0;
    CAutonomousIterator<NucSequence> it1(seq1);
    CAutonomousIterator<NucSequence> it2(seq2);
    while(!it1.end())
    {
        if((*it1)!=(*it2))
            ++h;
        ++it1;
        ++it2;
    }
    return h;
}

