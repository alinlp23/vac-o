/* 
 * File:   SubjectMock.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 13, 2010, 4:41 PM 
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

#ifndef _SUBJECTMOCK_H
#define	_SUBJECTMOCK_H

#include <gmock/gmock.h>
#include "ISubject.h"

template<class Subject>
class SubjectMock : public ISubject<Subject>
{
public:
    MOCK_METHOD1_T(attach, void(IObserver<Subject>*));
    MOCK_METHOD0_T(detach, void(IObserver<Subject>*));
    MOCK_CONST_METHOD1_T(notify, void(const Subject*));

    void SubjectAttach(IObserver<Subject>* o){ ISubject<Subject>::attach(o); }
    void SubjectDetach(IObserver<Subject>* o) throw(ElementNotFound) { ISubject<Subject>::detach(o); }
    void SubjectNotify(const Subject* s) const { ISubject<Subject>::notify(s); };
};

#endif	/* _SUBJECTMOCK_H */

