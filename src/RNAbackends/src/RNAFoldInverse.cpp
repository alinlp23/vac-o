#include <cstdlib>

#include "RNAFoldInverse.h"

extern "C" float viennaRNA_inverse_fold(char*, char*);

RNAFoldInverse::RNAFoldInverse(const NucSequence& start, const SecStructure& structure) :
start(start), structure(structure)
{}

void RNAFoldInverse::fold_inverse(NucSequence& sequence) throw(RNABackendException)
{
    size_t seq_size = start.length();

    char* c_start = (char*)calloc(seq_size+1, sizeof(char));
    char* c_struct = (char*)calloc(seq_size+1, sizeof(char));
    structure.copy(c_struct, seq_size);

    for(size_t idx=0; idx<seq_size; idx++)
    {
        c_start[idx] = to_str(start[idx])[0];
    }
    
    float d;
    do{
        d = viennaRNA_inverse_fold(c_start, c_struct);        
    }while(d!=0);

    sequence = string(c_start);

    free(c_start);
    free(c_struct);    
}

