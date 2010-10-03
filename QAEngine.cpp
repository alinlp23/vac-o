#include "QAEngine.h"
#include <iostream>
using std::cout;
using std::endl;
QAEngine::QAEngine(Depth depth, const QARegionsCt& regions):
depth(depth), regions(regions)
{}

void QAEngine::update(const NucSequence* candidate)
{
    cout << "QA validation for: " << *candidate << endl;
    if(validate(*candidate))
        notify(candidate);
}

bool QAEngine::validate(const NucSequence& sequence) const
{
    //validate the sequence using the QARegions
    return true;
}
