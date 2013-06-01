/*
 * File:   SimilitudeCmp.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 11, 2010, 7:54 PM
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

#ifndef _SIMILITUDECMP_H
#define _SIMILITUDECMP_H

enum SimilitudePolicy
{
    MinSimilitude, MaxSimilitude
};

template<SimilitudePolicy p>
struct SimilitudeCmp
{
    static inline bool cmp(fideo::Similitude s1, fideo::Similitude s2)
    {
        return s1 <= s2;
    }
};

template<>
struct SimilitudeCmp<MaxSimilitude>
{
    static inline bool cmp(fideo::Similitude s1, fideo::Similitude s2)
    {
        return s1 >= s2;
    }
};

#endif  /* _SIMILITUDECMP_H */

