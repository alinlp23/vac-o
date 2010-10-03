#include <cstdlib>

#include "RNAFoldInverse.h"

extern "C" float viennaRNA_inverse_fold(char*, char*);

RNAFoldInverse::RNAFoldInverse(const NucSequence& start, const SecStructure& structure) :
start(start), structure(structure)
{}

void RNAFoldInverse::fold_inverse(NucSequence& sequence) throw(RNABackendException)
{
    size_t seq_size = start.size();

    char* c_start = (char*)calloc(seq_size+1, sizeof(char));
    char* c_struct = (char*)calloc(seq_size+1, sizeof(char));
    structure.copy(c_struct, seq_size);
    start.copy(c_start, seq_size);

    /**
     * What should we do here?
     * inverse_fold from RNAPackage returns (or it seems so...)
     * 0 if it found a sequence with mfe structure
     * otherwise, the structure distance between the target, and what it found.
     *
     * If we are looking for exact solutions, we should keep calling
     * inverse_fold until it returns 0 (this could be "forever"...)
     */
    viennaRNA_inverse_fold(c_start, c_struct);

    sequence = c_start;

    free(c_start);
    free(c_struct);    
}

