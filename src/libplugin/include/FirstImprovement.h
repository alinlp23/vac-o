/* 
 * File:   FirstImprovement.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 14, 2010, 6:36 PM 
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

#ifndef _FIRSTIMPROVEMENT_H
#define	_FIRSTIMPROVEMENT_H

#include "Strategy.h"

class FirstImprovement : public Strategy
{
    virtual bool select_neighbor();
    virtual bool update(const ISolution*);
public:
    FirstImprovement(const INeighborhood*, Iteration, Iteration);
};

#endif	/* _FIRSTIMPROVEMENT_H */

