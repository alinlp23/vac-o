#include "IFold.h"
#include "IStructureCmp.h"
#include "SSValidator.h"

SSValidator::SSValidator(const IFold* fb, const IStructureCmp* strb, 
        const SecStructure& str, Similitude simil, SimilitudePolicy sp) :
        fold_backend(fb), struct_cmp_backend(strb), target_structure(str),
        similitude(simil), cmp_policy(sp)
{}

bool SSValidator::validate(const NucSequence& seq) const
{
    SecStructure seq_struct;
    fold_backend->fold(seq, seq_struct);
    const Similitude s = struct_cmp_backend->compare(target_structure, seq_struct);
    
    return cmp_policy == MinSimilitude ? similitude <= s : similitude >= s;
}
