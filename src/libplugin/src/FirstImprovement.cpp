#include "FirstImprovement.h"
#include <iostream>
FirstImprovement::FirstImprovement(const INeighborhood* ne, Iteration max, Iteration max_idle):
Strategy(ne,max, max_idle){}

bool FirstImprovement::select_neighbor()
{
    //nothing to do here.
    //Return if the neighbor was selected during the neighborhood exploring or not.
    return selected_neighbor!=NULL && selected_neighbor!=current_solution;
}

bool FirstImprovement::update(const ISolution* neighbor)
{
    bool done(false);
    Score ns = scorer->evaluate(neighbor);    
    if(ns >= current_score){
        selected_neighbor = neighbor;
        selected_neighbor_score = ns;
        done = true;
    }
    else
        delete neighbor;

    return done;
}
