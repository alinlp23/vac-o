/* 
 * File:   Combinator.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 21, 2010, 9:37 AM 
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

#ifndef _COMBINATOR_H
#define	_COMBINATOR_H

#include <vector>
using std::vector;

template <class C>
class Combinator
{
public:
    typedef typename C::value_type CType;
    typedef vector<CType> Combination;

    bool next(Combination& comb);
    void update(size_t n);
    Combinator(const C& e, size_t n);
private:
    typedef typename C::const_iterator ConstIterator;
    C elements;
    Combination combination;
    
    size_t k;

    ConstIterator end;
    ConstIterator start;
    ConstIterator kit;

    void move();
    void begin();
};

/**
 * Implementation
 */

template<class C>
Combinator<C>::Combinator(const C& e, size_t n) : elements(e), combination(n), k(n), end(), start(), kit()
{
    begin();
}

template<class C>
void Combinator<C>::update(size_t n)
{
    k = n;
    combination.clear();
    combination.resize(n);
    begin();
}

template<class C>
void Combinator<C>::begin()
{
    start = elements.begin();
    end = elements.end();
    move();
}

template<class C>
void Combinator<C>::move()
{
    ConstIterator it = start;
    for(size_t i = 0; i<k; ++i)
    {
        combination[i] = *it;
        if (i == k-1)
            kit = it;
        ++it;
    }
}

template<class C>
bool Combinator<C>::next(Combination& comb)
{
    bool more(true);

    if(kit != end)
    {
        comb = combination;
        ++kit;
        if(kit == end && k>1)
        {
            ++start;
            move();
        }
        else
            combination[k-1] = *kit;
    }
    else
        more = false;

    return more;
}

#endif	/* _COMBINATOR_H */

