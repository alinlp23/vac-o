/* 
 * File:   Subject.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 1, 2010, 11:07 AM 
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

#ifndef _SUBJECT_H
#define	_SUBJECT_H

template<class Subject>
void ISubject<Subject>::attach(Observer* o){
    insert_into(observers, o);
}

template<class Subject>
void ISubject<Subject>::detach(Observer* o) throw(ElementNotFound)
{
    if(!remove_first_from(observers, o)){
        throw ElementNotFound();
    }
}

template<class Subject>
void ISubject<Subject>::notify(const Subject* s) const{
    ObserversIterator it(observers);
    while(!it.end()){
        (*it)->update(s);
        ++it;
    }
}

template<class Subject>
void ISingleSubject<Subject>::set(Observer* o){
    observer = o;
}

template<class Subject>
void ISingleSubject<Subject>::unset()
{
    observer = NULL;
}

template<class Subject>
bool ISingleSubject<Subject>::notify(const Subject* s) const{
    bool status(false);
    if(observer)
        status = observer->update(s);

    return status;
}

#endif	/* _SUBJECT_H */

