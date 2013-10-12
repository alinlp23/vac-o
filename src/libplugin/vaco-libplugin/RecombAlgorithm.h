#ifndef _RecombAlgorithm_H
#define _RecombAlgorithmr_H

#include <biopp/biopp.h>
#include <list>
#include "vaco-commons/RecombinantInfo.h"

class RecombAlgorithm
{ 
    typedef std::list<int> Positions;
    static inline void insert(const biopp::NucSequence& seq,unsigned int from, unsigned int to, biopp::NucSequence& res);
    static inline void partition(const biopp::NucSequence& s1, const biopp::NucSequence& s2, unsigned int start, unsigned int despegue,  unsigned int aterrizaje,  unsigned int end,  biopp::NucSequence& seq);
    static inline void flat(const RecombinantInfo::RecombinantRegions& regions, Positions& flattened);
    static inline void oneCombination(const Positions& despegues, const Positions& aterrizajes, const biopp::NucSequence& s1, const biopp::NucSequence& s2, std::list<biopp::NucSequence>& results);
    static inline void combination(const Positions& positionsS1, const Positions& positionsS2, const biopp::NucSequence& s1, const biopp::NucSequence& s2, std::list<biopp::NucSequence>& results);

    const RecombinantInfo& recombinantSequenceInfo;
    const RecombinantInfo::RecombinantSequenceInfo& sequenceInfo;
public:
    RecombAlgorithm(const RecombinantInfo& recomb, const RecombinantInfo::RecombinantSequenceInfo& sequenceInfo);
    void run(std::list<biopp::NucSequence>& results);//TODO: getNext with mili::Coroutine
};



inline void RecombAlgorithm::insert(const biopp::NucSequence& seq,unsigned int from, unsigned int to, biopp::NucSequence& res) 
{
    for(unsigned int i = from; i != to; ++i)
        res.addNucleotide(seq[i]);    
}

inline void RecombAlgorithm::partition(const biopp::NucSequence& s1, const biopp::NucSequence& s2, unsigned int start, unsigned int despegue,  unsigned int aterrizaje,  unsigned int end,  biopp::NucSequence& seq) 
{
    insert(s1, start, despegue, seq);
    insert(s2, despegue, aterrizaje, seq);
    insert(s1, aterrizaje, end, seq);
}


inline void RecombAlgorithm::flat(const RecombinantInfo::RecombinantRegions& regions, Positions& flattened)
{
    for(RecombinantInfo::RecombinantRegions::const_iterator it = regions.begin(); it != regions.end(); ++it)
    {
        assert(it->start <= it->end);
        for (unsigned int i = it->start; i <= it->end; ++i)
            flattened.push_back(i);
    }
}

inline void RecombAlgorithm::oneCombination(const Positions& despegues, const Positions& aterrizajes, const biopp::NucSequence& s1, const biopp::NucSequence& s2, std::list<biopp::NucSequence>& results) 
{
    const unsigned int start = 0;
    const unsigned int end = s1.length();

    for(Positions::const_iterator despegue = despegues.begin(); despegue != despegues.end(); ++despegue) 
    {
        for(Positions::const_iterator aterrizaje = aterrizajes.begin(); aterrizaje != aterrizajes.end(); ++aterrizaje) 
        {
            if(*despegue < *aterrizaje) 
            {                
                /*biopp::NucSequence seq;
                partition(s1, s2, start, *despegue, *aterrizaje, end, seq);
                results.push_back(seq);*/
            }
        }
    }
}

inline void RecombAlgorithm::combination(const Positions& positionsS1, const Positions& positionsS2, const biopp::NucSequence& s1, const biopp::NucSequence& s2, std::list<biopp::NucSequence>& results) 
{
    oneCombination(positionsS1, positionsS2, s1, s2, results);
    oneCombination(positionsS2, positionsS1, s2, s1, results);
}

RecombAlgorithm::RecombAlgorithm(const RecombinantInfo& recomb, const RecombinantInfo::RecombinantSequenceInfo& sequenceInfo)
  : recombinantSequenceInfo(recomb),
    sequenceInfo(sequenceInfo)
{}

void RecombAlgorithm::run(std::list<biopp::NucSequence>& results) 
{
    Positions positionsrRecomb;
    Positions positions;
    flat(sequenceInfo.regions, positions);
    for(RecombinantInfo::RecombinantSequences::const_iterator it = recombinantSequenceInfo.recombinantSequences.begin();
        it != recombinantSequenceInfo.recombinantSequences.end();
        ++it)
    {
        flat(it->regions, positionsrRecomb);
        combination(positions, positionsrRecomb, sequenceInfo.sequence, it->sequence, results);
    }
}

#endif