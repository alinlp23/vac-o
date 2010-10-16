#include "Solution.h"

Solution::Solution(const NucSequence& seq, const CombinatoryRegionsCt& regions):sequence(seq)
{
    CAutonomousIterator<CombinatoryRegionsCt> it(regions);
    SeqIndex start;
    SeqIndex end;
    while (!it.end())
    {
        (*it)->get_bounds(start, end);
        string c;
        for (size_t idx=start; idx<end; ++idx)
        {
            c.append(to_str(seq[idx]));
        }
        //default local score = 1
        LocalOptimization op(c, 1);
        insert_into(components, op);
        ++it;
    }
}

Solution::Solution(const NucSequence& seq, const LocalOptimizationCt& comp) :
        sequence(seq), components(comp)
{}

void Solution::update_solution(RegionIdx r, const NucSequence& seq, const LocalOptimization& op)
{
    components[r] = op;
    sequence = seq;
}

void Solution::get_sequence(NucSequence& seq) const
{
    seq = sequence;
}

Score Solution::compute_local_score(RegionIdx exclude) const
{
    Score score = 1;
    for (RegionIdx i = 0; i<components.size(); ++i)
    {
        if (i != exclude)
            score *= components[i].second;

        ++i;
    }
    return score;
}

ISolution* Solution::clone() const
{
    return new Solution(sequence, components);
}
