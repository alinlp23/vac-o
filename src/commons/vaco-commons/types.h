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
#define _TYPES_H

#include <string>
#include <list>
#include <set>
#include <utility>

#include <biopp/biopp.h>

using biopp::NucSequence;
using biopp::AminoSequence;
using biopp::Triplet;

typedef std::list<NucSequence> NucSequencesCt;

/**
 * ICombinatoryEngine threshold cutoff
 */
typedef float CutOff;

/**
 * SSRegion cache
 */
typedef unsigned int CacheSize;

/**
 * Number of mutations
 */
typedef unsigned int NMutations;

/**
 * IQAEngine depth validation
 */
typedef unsigned int Depth;

/**
 * Sequence's score
 */
typedef float Score;

/**
 * Filename path
 */
typedef string Path;

/**
 * Ranking size
 */
typedef unsigned int RankingSize;

/**
 * Local search Iterations
 */
typedef unsigned int Iteration;

/**
 * Local optimization used for local search
 */
typedef std::pair<NucSequence, Score> LocalOptimization;

/**
 * Container of local optimizations
 */
typedef std::vector<LocalOptimization> LocalOptimizationCt;

/**
 * Index of a solution region.
 */
typedef unsigned int RegionIdx;

/**
 * Number of attemps to do something.
 */
typedef unsigned int Attempts;

#endif  /* _TYPES_H */

