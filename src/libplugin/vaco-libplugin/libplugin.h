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
#define _LIBPLUGIN_H

#include <mili/mili.h>
#include "vaco-commons/IPlugin.h"

/*Parameters*/
#include "vaco-commons/Parameter.h"

/*Combinatory regions*/
#include "vaco-libplugin/SSRegion.h"
#include "vaco-libplugin/GCRegion.h"

/*QA regions*/
#include "vaco-libplugin/AllMutator.h"
#include "vaco-libplugin/RandomMutator.h"
#include "vaco-libplugin/QARegion.h"

/*libRNA providers*/
#include "vaco-rna-backends/Hamming.h"

/*LocalSearch*/
#include "vaco-libplugin/Solution.h"
#include "vaco-libplugin/Strategy.h"
#include "vaco-libplugin/Neighborhood.h"
#include "vaco-libplugin/FirstImprovement.h"
#include "vaco-libplugin/BestImprovement.h"
#include "vaco-libplugin/SimulatedAnnealing.h"

#endif  /* _LIBPLUGIN_H */

