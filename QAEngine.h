/* 
 * File:   QAEngine.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 27, 2010, 3:52 PM 
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

#ifndef _QAENGINE_H
#define	_QAENGINE_H

#include "IQAEngine.h"

class QAEngine : public IQAEngine
{
    static QAEngine* instance;
    Depth depth;
    list<IQARegion> regions;
protected:
    QAEngine();
public:
    void set_depth(Depth d);
    void add_region(IQARegion* region);
    bool validate(const NucSequence& sequence) const;

    static QAEngine* get_instance();
};

#endif	/* _QAENGINE_H */

