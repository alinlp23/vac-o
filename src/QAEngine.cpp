#include "QAEngine.h"
#include <iostream>
using std::cout;
using std::endl;
QAEngine::QAEngine(Depth depth, const QARegionsCt& regions):
depth(depth), regions(regions)
{}

void QAEngine::update(const SequenceOptimization* candidate)
{
    cout << "QA validation for: ";
    for (size_t i = 0; i < (candidate->first).length(); ++i)
    {
        cout << to_str((candidate->first)[i]);
    }
    cout << endl;
    if(validate(candidate->first))
        notify(candidate);
}

bool QAEngine::validate(const NucSequence& sequence) const
{
    //validate the sequence using the QARegions
    return true;
}
