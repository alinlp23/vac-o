/*
 * File:   main.cpp
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 3:15 PM
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

/*observer&subjec*/
#include "IObserver.h"
#include "ISubject.h"

/*combinatory*/
#include "CombinatoryEngine.h"
#include "ICombinatoryRegion.h"
#include "CombinatoryRegion.h"
#include "SSRegion.h"
#include "GCRegion.h"

/*validator*/
#include "QAEngine.h"
#include "IQARegion.h"
#include "QARegion.h"
#include "IQAValidator.h"
#include "IQAMutator.h"

/*mutator*/
#include "ISequenceMutator.h"
#include "SequenceMutator.h"

/*ranker*/
#include "SequenceRanker.h"

/*pluginadmin*/
#include "PluginAdmin.h"

/*libRNA*/
#include "IFold.h"
#include "IFoldInverse.h"
#include "IStructureCmp.h"
#include "ISequenceCmp.h"

/*plugin*/
#include "IPlugin.h"


int main(int argc, char** argv) {
    /*
     * Pseudo main program...
     *
     * PluginAdmin plg_admin;
     * IPlugin* plg = plg_admin.load(plg_path);
     *     
     * CombinatoryEngine comb_engine(plg);
     * QAEngine qa_engine(plg);
     * SequenceEvaluator evaluator(plg);
     * SequenceRanker ranker(plg);
     *
     * evaluator.attach(&ranker);
     * qa_engine.attach(&evaluator);
     * comb_engine.attach(&qa_engine);
     *
     * comb_engine.run();
     *
     * print_ranking(ranker)
     * plg->unload();
     *
     */
    return 0;
}
