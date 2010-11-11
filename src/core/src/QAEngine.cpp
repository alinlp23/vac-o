#include <mili/mili.h>
#include "QAEngine.h"
#include <iostream>
using std::cout;
using std::endl;
QAEngine::QAEngine(const QARegionsCt& regions):
        regions(regions)
{}

void QAEngine::update(const SequenceOptimization* candidate)
{
    cout << "QA validation for: ";
    for (size_t i = 0; i < (candidate->first).length(); ++i)
    {
        cout << to_str((candidate->first)[i]);
    }
    cout << endl;
    if (validate(candidate->first))
        notify(candidate);
}

bool QAEngine::validate(const NucSequence& sequence) const
{
    //validate the sequence using the QARegions
    CAutonomousIterator<QARegionsCt> rs(regions);
    bool pass(true);
    while (!rs.end() && pass)
    {
        pass = (*rs)->validate(sequence);
        ++rs;
    }
    return pass;
}
