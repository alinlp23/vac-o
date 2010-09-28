/* 
 * File:   Ranker.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 4:12 PM 
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

#ifndef _RANKER_H
#define	_RANKER_H

#include <set>
#include "IRanker.h"

using std::set;

class Ranker : public IRanker
{
    static Ranker* instance;
    struct RSec{
        Score score;
        NucSequence sequence;
        bool operator() (const RSec& ls, const RSec& hs) const
            {return ls.score<hs.score;}
    };
    set<RSec, RSec> ranking;
    set<RSec, RSec>::iterator it;
protected:
    Ranker();
public:
    void update(const NucSequence& sequence, Score s);
    
    void begin();
    float current(NucSequence& sequence);
    void next();
    bool done() const;

    static Ranker* get_instance();
};

#endif	/* _RANKER_H */

