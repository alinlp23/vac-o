#include <cstdlib>

#include "RNAFold.h"

extern "C" float viennaRNA_fold(char*, char*);

Fe RNAFold::fold(const NucSequence& sequence, SecStructure& structure) const throw(RNABackendException)
{    
    size_t seq_size = sequence.length();

    char* c_seq = (char*)calloc(seq_size+1, sizeof(char));
    char* c_struct = (char*)calloc(seq_size+1, sizeof(char));
        
    //sequence.copy(c_seq, seq_size);
    Fe energy = viennaRNA_fold(c_seq, c_struct);    

    structure = c_struct;

    free(c_seq);
    free(c_struct);
    
    return energy;
}