#include "SSRegion.h"
#include "IFoldInverse.h"
#include "IStructureCmp.h"
#include "ISequenceCmp.h"
#include "SequenceMutator.h"
#include "IFold.h"

SSRegion::SSRegion(SeqIndex s, SeqIndex e, const SecStructure& wt,
                   const SecStructure& vaccine, NMutations nm, Similitude simi,
                   Distance dis, const NucSequencesCt& wt_cache, const IFold* const fb,
                   IFoldInverse* const fib, const IStructureCmp* const str_cmp,
                   const ISequenceCmp* const seq_cmp) :
        CombinatoryRegion(s, e),
        wt_structure(wt), vaccine_structure(vaccine), max_mutations(nm),
        max_similitude(simi), min_distance(dis), wildtype_cache(wt_cache),
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
    cout << "Local score for:" << endl;
    for (size_t i=0; i<sequence.length(); ++i)
    {
        cout << to_str(sequence[i]);
    }
    cout << endl;
    cin >> s;
    return s;
}

Score SSRegion::generate(NucSequence& sequence, NucSequence& delta)
{
    bool pass;
    do
    {
        inverse_backend->fold_inverse(delta);
        sequence = base_sequence;
        for (size_t idx=0; idx<delta.length(); ++idx)
        {
            sequence[start+idx] = delta[idx];
        }
        pass = cache_compare(sequence) && structure_compare(sequence);
    }
    while (!pass);
    //If the sequence pass both filters, we accept it.
    return evaluate(delta);
}

void SSRegion::set_base_sequence(const NucSequence& sequence)
{
    base_sequence = sequence;
    inverse_backend->query_start(this);
}

void SSRegion::get_partial_start(IFoldInverse* const backend)
{
    string tmp;
    for (size_t idx = start; idx<end; ++idx)
    {
        tmp += to_str(base_sequence[idx]);
    }
    NucSequence partial = tmp;
    backend->set_start(partial);
}

void SSRegion::get_complete_start(IFoldInverse* const backend)
{
    backend->set_start(base_sequence);
}

bool SSRegion::cache_compare(const NucSequence& seq)
{
    CAutonomousIterator<NucSequencesCt> it(wildtype_cache);
    bool pass(true);
    while (!it.end() && pass)
    {        
        pass = min_distance < seq_cmp_backend->compare(seq, *it);
        ++it;
    }
    return pass;
}

bool SSRegion::structure_compare(const NucSequence& seq)
{
    SequenceMutator mutator(seq, max_mutations);
    NucSequence mutated;
    SecStructure mutated_struct;
    bool pass(true);

    while (mutator.next(mutated) && pass)
    {
        fold_backend->fold(mutated, mutated_struct);
        pass = max_similitude > struct_cmp_backend->compare(wt_structure, mutated_struct);
    }
    return pass;
}