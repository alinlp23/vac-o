#include "CombinatoryEngine.h"
#include "IPlugin.h"
#include <iostream>
using std::cout;
using std::endl;

CombinatoryEngine::CombinatoryEngine(const NucSequence& seq, const CombinatoryRegionsCt& rs,
                                     CutOff c, const IPlugin* const plg) :
sequence(seq), cutoff(c), regions(rs), plg(plg)
{}

void CombinatoryEngine::run()
{    
    /*
     * while(!plg->done())
     * {
     *     get a new sequence s
     *     notify(s);
     * }
     *
     */
    cout << "Running Combinatory engine..." << endl;
    NucSequence s1 = "AAUAGA";
    notify(&s1);
    NucSequence s2 = "AAUAGU";
    notify(&s2);
    NucSequence s3 = "GGUAGU";
    notify(&s3);
}
