#include "Hamming.h"
#include <mili/mili.h>

Distance Hamming::compare(const NucSequence& seq1,
                          const NucSequence& seq2) const throw(RNABackendException)
{
    /*This could be optional*/
    if(seq1.length() != seq2.length())
        throw RNABackendException("Hamming distance must be calculated over sequences of the same size");

    Distance h=0;

    for(size_t idx=0; idx<seq1.length(); idx++)
    {
        if(seq1[idx] != seq2[idx])
            ++h;        
    }
    return h;
}

