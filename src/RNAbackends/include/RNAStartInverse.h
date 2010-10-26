/* 
 * File:   RNAStartInverse.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 25, 2010, 12:25 PM 
 *
 * Copyright (C) 2010  Santiago Videla, FuDePAN
 *
 * This file is part of vac-o
 *
 * vac-o is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * vac-o is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vac-o.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef _RNASTARTINVERSE_H
#define	_RNASTARTINVERSE_H

#include <string>
#include "IFoldInverse.h"
#include "types.h"
#include "Combinator.h"

using std::string;
/**
 * Base class implementation for RNA inverse folding
 * backends that accept a start sequence.
 * (e.g. RNAinverse or INFO-RNA)
 *
 * This class takes care of avoid repeated sequences
 * and change the free positions in the start sequence
 * when the attempts for each combination it's reached.
 */
class RNAStartInverse : public IFoldInverse
{
    static const char WILDCARD = 'N';
    string rstart;
    StringSequencesCt found;
    const Attempts combination_attempts;
    SeqIndexesCombinator* const combinator;
    SeqIndexesCombination positions;

    virtual void fold_inverse(NucSequence&) throw(RNABackendException);
    virtual void set_start(const NucSequence&);

    void change_start();
protected:
    string start;
    const SecStructure structure;
    Similitude max_structure_distance;
    Distance max_sequence_distance;

    /**
     * To be implemented in the concrete backend.
     * Should call the backend algorithm and parse the result correctly.
     * @param seq to write the sequence found.
     * @param hd  to write the hamming distance between the start and found.
     * @param sd  to write the structure distance between the found and target
     */
    virtual void execute(string&, Distance&, Similitude&) throw(RNABackendException) = 0;
public:
    RNAStartInverse(const SecStructure&, Similitude, Distance, Attempts);
    RNAStartInverse(const RNAStartInverse&);
    RNAStartInverse& operator=(const RNAStartInverse&);

    ~RNAStartInverse();
};


#endif	/* _RNASTARTINVERSE_H */

