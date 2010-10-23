#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <mili/mili.h>

using std::string;
using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::find_if;
using std::transform;

#include "RNAFoldInverse.h"

RNAFoldInverse::RNAFoldInverse(const SecStructure& structure, Similitude sd, Distance hd, Attempts ca) :
        start(), rstart(), structure(structure), max_structure_distance(sd), max_sequence_distance(hd),
        cmd(), found(), combination_attempts(ca) ,combinator(), positions()
{
    stringstream ss;
    int repeat = max_structure_distance == 0 ? -1 : 1;
    ss << "RNAinverse -R " << repeat << " -a ATGC < inverse.in > inverse.out";
    cmd = ss.str();

    list<SeqIndex> range;
    for(SeqIndex i=0; i<structure.size(); ++i)
    {
        range.push_back(i);
    }
    combinator = new SeqIndexesCombinator(range, hd);
}

RNAFoldInverse::~RNAFoldInverse()
{
    delete combinator;
}

void RNAFoldInverse::fold_inverse(NucSequence& sequence) throw(RNABackendException)
{
    string seq;
    Distance hd;
    Similitude sd;
    list<string>::const_iterator search;
    Attempts i = combination_attempts;
    do
    {
        --i;
        //This is only relevant when max_structure_distance > 0
        //Otherwise, RNAinverse will take care to return only
        //sequences with sd = 0.
        do
        {
            execute(seq, hd, sd);
        }
        while (sd > max_structure_distance);                

        //We have to check if the sequence was already found in a previous
        //call for the current 'start'.
        SeqCmp cmp(seq);
        search = find_if(found.begin(), found.end(), cmp);

        //If the sequence found was already returned and we reach the number
        //of attempts for the current combination of free positions in 'start',
        //we move to the next combination, change the 'start' and re-start the
        //number of attempts.
        if (search != found.end() && i==0)
        {           
            combinator->next(positions);            
            change_start();
            i = combination_attempts;
        }
    }
    while (search != found.end());

    //Adds the sequence found to the list.
    found.push_back(seq);
    sequence = seq;
}

void RNAFoldInverse::set_start(const NucSequence& sequence)
{
    //clear any previous start and found list.
    start.clear();
    found.clear();
    //Sets the start in lowercase. We need this to avoid that RNAinverse
    //make changes everywhere.
    for (size_t i=0; i<sequence.length(); ++i)
    {        
        start += tolower(to_str(sequence[i])[0]);
    }
    //Adds the start to the list of found sequence.
    found.push_back(start);
    //rembember the original start.
    rstart = start;

    //Begin the combinator and set the first free positions.
    combinator->begin();
    combinator->next(positions);
    change_start();
}

void RNAFoldInverse::change_start()
{
    //Gets the original start
    start = rstart;
    CAutonomousIterator<SeqIndexesCombination> it(positions);
    while(!it.end())
    {
        //This let RNAinverse to search for possible changes in each position.
        start[*it] = '.';
        ++it;
    }    
}

void RNAFoldInverse::execute(string& seq, Distance& hd, Similitude& sd)
{
    ofstream out("inverse.in");
    out << structure << "\n";
    out << start << "\n";

    out.close();

    int status = system(cmd.c_str());
    if (status)
        throw RNABackendException("An error ocurred trying to execute: "+cmd);

    ifstream in("inverse.out");

    string aux;
    getline(in, aux);
    /* aux looks like this
     * accagggATCgcaggtaccccgcaGGcgcagAacccta   5 2   d= 2
     *
     * where uppercases were set by RNAinverse (dots in our start).
     * 5 it's the hamming distance from the random generated start and the
     * sequence found. And 2 it's the structure distance to the target structure.
     * If max_structure_distance=0 then, this will be also equal to 0.
     */

    //sequence found
    seq = aux.substr(0, start.size());
    for (size_t i=0; i<start.size(); ++i)
    {
        //all to lower because we will need to compare this sequence with the
        //sequences in found list.
        seq[i] = tolower(aux[i]);
    }

    //hamming distance from the start used
    int from = aux.find_first_not_of(" ", start.size());
    int to = aux.find_first_of(" ", from);
    from_string<Distance>(aux.substr(from, to-from), hd);

    //structure distance from the sequence found to the target structure.
    from = aux.find_first_not_of(" ", to);
    to = aux.find_first_of(" ", from);
    from_string<Similitude>(aux.substr(from, to-from), sd);
}