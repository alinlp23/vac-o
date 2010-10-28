#include "Hamming.h"
#include <mili/mili.h>

Hamming::Hamming() : matrix()
{
    initialize_distance_matrix();
}

Hamming::Hamming(const IDistanceMatrixProvider* const provider) : matrix()
{
    initialize_distance_matrix();
    provider->get_distance_matrix(matrix);
}

void Hamming::initialize_distance_matrix()
{
    for (size_t i = 0; i < MATRIX_SIZE; ++i)
    {
        for (size_t j = 0; j < MATRIX_SIZE; ++j)
            matrix[i][j] = i==j ? 0.f : 1.f;
    }
}

Distance Hamming::compare(const NucSequence& seq1,
                          const NucSequence& seq2) const throw(RNABackendException)
{
    
    if (seq1.length() != seq2.length())
        throw RNABackendException("Hamming distance must be calculated over sequences of the same size");
    
    Distance h = 0.f;
    for (size_t i=0; i<seq1.triplets_length(); ++i)
    {
        Triplet t1 = seq1.get_triplet(i);
        Triplet t2 = seq2.get_triplet(i);

        h += t1.distance(t2, matrix);
    }
           
    return h;
}

