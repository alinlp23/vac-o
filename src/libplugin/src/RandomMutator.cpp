#include <mili/mili.h>
#include "rna_backends_types.h"
#include "RandomMutator.h"

inline void initialize_mutation_matrix(DistanceMatrix& matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE; ++i)
    {
        for (size_t j = 0; j < MATRIX_SIZE; ++j)
            matrix[i][j] = i==j ? 0.f : 1.f/3.f;
    }
}

RandomMutator::RandomMutator(NMutations mutations, NMutations mutants) :
        sequence(), mutations(mutations), mutants(mutants), counter(0), matrix(), rnd(0.f,1.f)
{
    initialize_mutation_matrix(matrix);    
}

RandomMutator::RandomMutator(NMutations mutations, NMutations mutants, const IMutationMatrixProvider* provider) :
sequence(), mutations(mutations), mutants(mutants), counter(0), matrix(), rnd(0,1)
{
    initialize_mutation_matrix(matrix);
    provider->get_mutation_matrix(matrix);
}

bool RandomMutator::next(NucSequence& seq)
{
    ++counter;
    bool more(counter <= mutants);
    
    if(more)
    {        
        seq = sequence;
        NMutations i = 0;
        const size_t length = sequence.length();
        while (i<mutations)
        {
            const SeqIndex pos = int(rnd.get()*length);
            const float prob = rnd.get();

            Nucleotide b = Nucleotide(0);
            float acc = matrix[seq[pos]][b];
            while (acc < prob)
            {
                b = Nucleotide((b + 1) % 4);
                acc += matrix[seq[pos]][b];
            }
            seq[pos] = b;

            ++i;
         }
    }
    return more;
}

void RandomMutator::set_base_sequence(const NucSequence& seq)
{
    sequence = seq;
    counter = 0;
}
