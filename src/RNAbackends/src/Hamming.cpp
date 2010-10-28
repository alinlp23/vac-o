#include "Hamming.h"

Hamming::Hamming() : matrix()
{
    initialize_distance_matrix(matrix);
}

Hamming::Hamming(const IDistanceMatrixProvider* const provider) : matrix()
{
    initialize_distance_matrix(matrix);
    provider->get_distance_matrix(matrix);
}

Distance Hamming::compare(const NucSequence& seq1,
                          const NucSequence& seq2) const throw(RNABackendException)
{
    
    if (seq1.length() != seq2.length())
        throw RNABackendException("Hamming distance must be calculated over sequences of the same size");
    
    Distance h = 0.f;
    const size_t n_triplets = seq1.triplets_length();
    for (size_t i=0; i<n_triplets; ++i)
    {
        const Triplet t1 = seq1.get_triplet(i);
        const Triplet t2 = seq2.get_triplet(i);

        h += t1.distance(t2, matrix);
    }
           
    return h;
}

