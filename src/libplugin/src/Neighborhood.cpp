#include "Neighborhood.h"

Neighborhood::Neighborhood(const CombinatoryRegionsCt& r, CutOff c, Attempts a):
        regions(r),cutoff(c), attempts(a)
{}

void Neighborhood::explore(const ISolution* current) const
{
    NucSequence cseq;
    current->get_sequence(cseq);
    RegionIdx r = 0;
    bool done(false);

    while (r<regions.size() && !done)
    {
        //sets the current solution's sequence as the base sequence
        regions[r]->set_base_sequence(cseq);
        //Compute local score without the region r
        Score cscore = current->compute_local_score(r);

        Attempts i = 0;
        while (i < attempts && !done)
        {
            NucSequence nseq;
            NucSequence ndelta;
            Score nscore = regions[r]->generate(nseq, ndelta);

            if (cscore*nscore >= cutoff)
            {
                ISolution* neighbor = current->clone();
                LocalOptimization op(ndelta, nscore);
                neighbor->update_solution(r, nseq, op);
                done = notify(neighbor);
            }
            ++i;
        }
        ++r;
    }
}

