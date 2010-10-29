#include "TripletsProductor.h"
#include <iostream>
TripletsProductor::TripletsProductor(const AminoSequence& aminoacids) :
        last(aminoacids.size()-1), more(aminoacids.size()>0),
        prod_it(aminoacids.size()), product(aminoacids.size())
{    
    for (size_t i = 0; i < aminoacids.size(); ++i)
    {
        TripletsIterator triplet_it = GeneticCode::triplets(aminoacids[i]);
        prod_it[i] = triplet_it;        
        product[i] = *(prod_it[i]);
        
    }
}
bool TripletsProductor::next(TripletsProduct& p)
{
    bool cont(more);
    p = product;
    move(last);
    return cont;
}

void TripletsProductor::move(size_t i)
{
    ++prod_it[i];
    if(prod_it[i].end())
    {
        prod_it[i].restart();
        if (i>0)
            move(i-1);
        else
            more = false;
    }
    product[i] = *(prod_it[i]);
}

