/* 
 * File:   IRanker.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 3:58 PM 
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

#ifndef _IRANKER_H
#define	_IRANKER_H

#include "biopp.h"


class IRanker {
public:
    virtual void update(NucSequence sequence, float score) = 0;
    
    virtual void begin() = 0;
    virtual float current(NucSequence& sequence) = 0;
    virtual void next() = 0;
    virtual bool done() = 0;

    virtual ~IRanker(){}
};

#endif	/* _IRANKER_H */

