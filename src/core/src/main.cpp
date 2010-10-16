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

/*combinatory*/
#include "CombinatoryEngine.h"

/*validator*/
#include "QAEngine.h"
#include "IQARegion.h"

/*ranker*/
#include "SequenceRanker.h"

/*pluginadmin*/
#include "PluginAdmin.h"

/*plugin*/
#include "IPlugin.h"
#include "Parameter.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void ask_for_parameters(ParamsCt& params){
    if(!params.empty())
    {
        CAutonomousIterator<ParamsCt> it(params);
        
        string aux;
        string param_name;
        bool valid;
        while (!it.end())
        {            
            (*it)->get_name(param_name);
            cout << "Enter value for "+param_name+": " << endl;
            cin >> aux;
            valid = (*it)->set_value(aux);
            if (valid)
                ++it;
            else
                cout << "Invalid value, try again." << endl;
        }
    }
}

void print_ranking(SequenceRanker& ranking)
{
    CAutonomousIterator<SequenceRanker> it(ranking);

    NucSequence seq;
    Score score;
    while (!it.end())
    {
        seq = (*it)->first;
        score = (*it)->second;
        for (size_t i = 0; i < seq.length(); ++i)
        {
            cout << to_str(seq[i]);
        }
        cout << " Score: " << score << endl;
        ++it;
    }
}

int main(int argc, char** argv) {
    PluginAdmin plg_admin;
    IPlugin* plg = plg_admin.load("libplugin/libplugin.so");

    ParamsCt params;
    plg->get_parameters(params);
    ask_for_parameters(params);
    plg->configure();
    
    CombinatoryEngine comb_engine(plg);

    QARegionsCt qa_regions;
    plg->get_qa_regions(qa_regions);
    QAEngine qa_engine(plg->get_qa_depth(), qa_regions);
    
    SequenceRanker ranker(plg->get_ranking_size());

    qa_engine.attach(&ranker);
    comb_engine.attach(&qa_engine);

    //run forest, run!!!
    comb_engine.run_forest();
    print_ranking(ranker);
    
    plg_admin.unload(plg); 
    return 0;
}
