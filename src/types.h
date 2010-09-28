/* 
 * File:   types.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 28, 2010, 2:50 PM 
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

#ifndef _TYPES_H
#define	_TYPES_H

/*CombinatoryEngine cutoff*/
typedef float CutOff;

/*Index position in a sequence*/
typedef unsigned int SeqPosition;

/*Distance between sequences*/
typedef unsigned int Distance;

/*Similitude between sequences or structures*/
typedef float Similitude;

/*SSRegion cache*/
typedef unsigned int CacheSize;

/*Number of mutations*/
typedef unsigned int NMutations;

/*QAEngine depth validation*/
typedef unsigned int Depth;

/*Sequence's score*/
typedef float Score;


#endif	/* _TYPES_H */

