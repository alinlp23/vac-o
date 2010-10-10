#include <string.h>
#include "fold_vars.h"
#include "fold.h"
#include "inverse.h"

float viennaRNA_fold(char* seq, char* structure)
{
    float mfe;
    initialize_fold(strlen(seq));
    mfe =  fold(seq, structure);
    free_arrays();
    return mfe;
}

float viennaRNA_inverse_fold(char* start, char* structure)
{
    float d;
    initialize_fold(strlen(start));    
    d = inverse_fold(start, structure);
    free_arrays();
    return d;
}
