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

Score SSRegion::evaluate(const NucSequence& sequence) const
{
    return 1;
}

Score SSRegion::generate(NucSequence& sequence, NucSequence& delta){
    return evaluate(delta);
}
