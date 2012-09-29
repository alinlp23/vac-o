/*
 * File:   IObserver.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 30, 2010, 4:41 PM
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

#ifndef _IOBSERVER_H
#define _IOBSERVER_H

/**
 * Interface for observers
 */
template<class Subject>
class IObserver
{
public:
    /**
     * Do something with the subject observed.
     * @param s the subject
     */
    virtual void update(const Subject* s) = 0;
    virtual ~IObserver() {}
};

/**
 * Interface for single observers
 */
template<class Subject>
class ISingleObserver
{
public:
    virtual ~ISingleObserver() {}
    /**
     * Do something with the subject observerd
     * @param s the subject
     * @return true or false that could be used by the SingleSubject
     * to stop notifying
     */
    virtual bool update(const Subject* s) = 0;
};

#endif  /* _IOBSERVER_H */

