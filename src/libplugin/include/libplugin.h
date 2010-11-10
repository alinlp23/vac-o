/*
 * File:   libplugin.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 1, 2010, 12:55 AM
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

#ifndef _LIBPLUGIN_H
#define	_LIBPLUGIN_H
#include <mili/mili.h>
#include "IPlugin.h"

/*Parameters*/
#include "Parameter.h"

/*Combinatory regions*/
#include "SSRegion.h"
#include "GCRegion.h"

/*QA regions*/
#include "AllMutator.h"
#include "RandomMutator.h"
#include "QARegion.h"

/*libRNA providers*/
#include "RNAFold.h"
#include "RNAinverse.h"
#include "INFORNA.h"
#include "RNAForester.h"
#include "Hamming.h"

/*LocalSearch*/
#include "Solution.h"
#include "Strategy.h"
#include "Neighborhood.h"
#include "FirstImprovement.h"

#endif	/* _LIBPLUGIN_H */

