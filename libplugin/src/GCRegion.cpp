#include "GCRegion.h"

GCRegion::GCRegion(SeqIndex s, SeqIndex e, const AminoSequence& aminoacids) :
        CombinatoryRegion(s, e), target_aminoacids(aminoacids),
        productor(new TripletsProductor(aminoacids)), rbase()
{}

GCRegion::~GCRegion()
{
    delete productor;
}

Score GCRegion::evaluate(const NucSequence& delta) const
{
    return 1.f;
}

Score GCRegion::generate(NucSequence& sequence, NucSequence& delta)
{
    TripletsProductor::TripletsProduct current_prod;    
    string raw;
    delta = rbase;
    const size_t ntriplets = delta.triplets_length();
    do
    {
        productor->next(current_prod);
        raw.clear();
        for (size_t i=0; i< ntriplets; ++i)
        {
            delta.set_triplet(i, current_prod[i]);
            raw += current_prod[i].to_string();
        }
    }
    while (raw == rbase);

    sequence = base_sequence;
    for (size_t idx=0; idx<delta.length(); ++idx)
        sequence[start+idx] = delta[idx];

    return evaluate(delta);
}

void GCRegion::set_base_sequence(const NucSequence& seq)
{
    base_sequence = seq;
    rbase.clear();
    for (size_t i=start; i<end; ++i)
    {
        rbase+=to_str(base_sequence[i]);
    }    
}