#include "QARegion.h"
#include "IQAMutator.h"
#include "IQAValidator.h"

#include <iostream>
using std::cout;
using std::endl;

QARegion::QARegion(SeqIndex s, SeqIndex e, Depth d, IQAMutator* m, const IQAValidator* v) :
        start(s), end(e), depth(d), mutator(m), validator(v)
{}

QARegion::~QARegion()
{
    delete mutator;
    delete validator;
}

bool QARegion::validate(const NucSequence& seq) const
{    
    Depth d = 0;
    queue<NucSequence> mutants;

    //Extract the region from the complete sequence
    NucSequence region;
    string str_r;
    for (SeqIndex i=start; i<end; ++i)
        str_r += to_str(seq[i]);
    region = str_r;
    
    mutants.push(region);
    bool pass = validator->validate(seq);

    while (d<depth && !mutants.empty() && pass)
    {
        const NucSequence current = mutants.front();
        mutants.pop();
        pass = validate_mutants(seq, current, mutants);
        ++d;
    }
    return pass;
}

bool QARegion::validate_mutants(const NucSequence& seq, const NucSequence& region, queue<NucSequence>& mutants) const
{
    bool pass(true);

    mutator->set_base_sequence(region);
    NucSequence mutant;
    NucSequence complete_mutant = seq;
    while (mutator->next(mutant) && pass)
    {
        //restore the complete sequence in order to validate it.
        for (SeqIndex i=0; i<mutant.length(); ++i)
            complete_mutant[start+i] = mutant[i];

        pass = validator->validate(complete_mutant);
        if (pass)
            mutants.push(mutant);
    }    
    return pass;
}
