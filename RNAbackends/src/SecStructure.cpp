#include "rna_backends_types.h"
#include <iostream>
using std::string;
using std::vector;

SecStructure::SecStructure()
{}

SecStructure::SecStructure(const string& structure) throw(InvalidStructureException) :
        vector<SeqIndex>(structure.size())
{
    parse_structure(structure, structure.size());
}

SecStructure& SecStructure::operator=(const string& str) throw(InvalidStructureException)
{    
    this->clear();
    if (!str.empty())
    {
        const size_t length = str.size();
        this->reserve(length);
        parse_structure(str, length);
    }
    return *this;
}

void SecStructure::pair(SeqIndex o, SeqIndex c) throw(InvalidStructureException)
{    
    if (c < o)
        throw(InvalidStructureException(" Open index must be lower than close index"));    
    else if (c-o < 4)
        throw(InvalidStructureException("Hairpin loop too small"));
    else if (c >= size())
        throw(InvalidStructureException("Close index out of range"));
    else
    {
        unpair(o);
        unpair(c);
        (*this)[o] = c;
        (*this)[c] = o;
    }        
}

void SecStructure::unpair(SeqIndex i)
{
    if (is_paired(i))
    {
        const SeqIndex unpaired = size();
        (*this)[(*this)[i]] = unpaired;
        (*this)[i] = unpaired;
    }
}

string SecStructure::to_str() const
{    
    const size_t length = size();
    string str;    
    for (SeqIndex i=0; i<length; ++i)
    {        
        if (is_paired(i))
        {            
            if (i<(*this)[i])
                str += OPEN_PAIR;
            else
                str += CLOSE_PAIR;
        }
        else
            str += UNPAIR;
    }    
    return str;
}

void SecStructure::parse_structure(const std::string structure, size_t length) throw(InvalidStructureException)
{
    if (size() == 0)
    {
        //We need this to make the vector aware of it's size
        //due to operator[] doesn't change the size of the vector.
        for (size_t i=0; i<length; ++i)
            this->push_back(length);
    }

    std::list<SeqIndex> stack;        
    for (size_t i = 0; i<length; ++i)
    {
        SeqIndex open;        
        switch (structure[i])
        {
            case UNPAIR:
                (*this)[i] = length;
                break;
            case OPEN_PAIR:
                stack.push_front(i);
                break;
            case CLOSE_PAIR:
                open = stack.front();                
                pair(open, i);
                stack.pop_front();
                break;
            default:
                throw(InvalidStructureException(" Unexpected symbol: "+structure[i]));
                break;
        }
    }    
    if (!stack.empty())
        throw(InvalidStructureException(" Pairs pending to close"));    
}


