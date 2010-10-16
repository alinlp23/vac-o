#include "SSRegion.h"

SSRegion::SSRegion(SeqIndex s, SeqIndex e, const SecStructure& wt,
            const SecStructure& vaccine, NMutations nm, Similitude simi, 
            Distance dis, const NucSequencesCt& wt_cache, const IFold* const fb,
            IFoldInverse* const fib, const IStructureCmp* const str_cmp,
            const ISequenceCmp* const seq_cmp) :
CombinatoryRegion(s, e),
wt_structure(wt), vaccine_structure(vaccine), max_mutations(nm),
max_similitude(simi), min_distance(dis), wildtype_cache(wt_cache), mutator(),
fold_backend(fb), inverse_backend(fib), struct_cmp_backend(str_cmp),
seq_cmp_backend(seq_cmp)
{}
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

Score SSRegion::evaluate(const NucSequence& sequence) const
{
    Score s;
    cout << "Local score:" << endl;
    cin >> s;
    return s;
}

Score SSRegion::generate(NucSequence& sequence, NucSequence& delta){
    string d;
    cout << "Generate: " << endl;
    cin >> d;
    delta = d;
    sequence = base_sequence;
    for(size_t idx=start; idx<end; ++idx)
    {
        sequence[idx] = delta[idx];
    }    
    return evaluate(delta);
}
