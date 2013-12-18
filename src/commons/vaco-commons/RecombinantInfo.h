#ifndef RECOMBINANTINFO_H
#define RECOMBINANTINFO_H

#include <list>
#include <biopp/biopp.h>

struct RecombinantInfo
{
    struct PositionsRange
    {
        PositionsRange(unsigned start, unsigned end)
            : start(start),
              end(end)
        {}

        PositionsRange(const PositionsRange& other)
            : start(other.start),
              end(other.end)
        {}

        const unsigned int start;
        const unsigned int end;
    };

    typedef std::list<PositionsRange> RecombinantRegions;

    struct RecombinantSequenceInfo
    {
        RecombinantRegions regions;
        biopp::NucSequence sequence;
    };

    RecombinantRegions candidateRegions;

    typedef std::list<RecombinantSequenceInfo> RecombinantSequences;

    RecombinantSequences recombinantSequences;
};

#endif  /* _IPLUGIN_H */
