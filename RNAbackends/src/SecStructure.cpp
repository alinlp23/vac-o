#include "rna_backends_types.h"
#include <stack>
#include <algorithm>
using std::stack;
using std::string;
using std::vector;
using std::swap;

SecStructure::SecStructure() : structure()
{}

SecStructure::SecStructure(const string& str) throw(InvalidStructureException) :
        structure(str.size())
{
    parse_structure(str, str.size());
}

SecStructure& SecStructure::operator=(const string& str) throw(InvalidStructureException)
{    
    structure.clear();
    if (!str.empty())
    {
        const size_t length = str.size();
        structure.reserve(length);
        parse_structure(str, length);
    }
    return *this;
}

void SecStructure::pair(SeqIndex o, SeqIndex c) throw(InvalidStructureException)
{    
    if (c < o)
        swap(o, c);

    if (c-o < 4)
        throw(InvalidStructureException("Hairpin loop too small"));
    else if (c >= size())
        throw(InvalidStructureException("Close index out of range"));
    else
    {
        unpair(o);
        unpair(c);
        structure[o] = c;
        structure[c] = o;
    }        
}

void SecStructure::unpair(SeqIndex i)
{
    if (is_paired(i))
    {
        const SeqIndex unpaired = unpaired_value();
        structure[structure[i]] = unpaired;
        structure[i] = unpaired;
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
            if (i<structure[i])
                str += OPEN_PAIR;
            else
                str += CLOSE_PAIR;
        }
        else
            str += UNPAIR;
    }    
    return str;
}

void SecStructure::parse_structure(const std::string& str, size_t length) throw(InvalidStructureException)
{
    
    structure.resize(length, length);
    const SeqIndex unpaired = unpaired_value();
    stack<SeqIndex> s;
    for (size_t i = 0; i<length; ++i)
    {        
        SeqIndex open;        
        switch (str[i])
        {
            case UNPAIR:
                structure[i] = unpaired;
                break;
            case OPEN_PAIR:
                s.push(i);
                break;
            case CLOSE_PAIR:
                if(!s.empty())
                {
                    open = s.top();
                    pair(open, i);
                    s.pop();
                }
                else
                    throw(InvalidStructureException(" Unexpected closing pair"));
                break;
            default:
                throw(InvalidStructureException(" Unexpected symbol: "+structure[i]));
                break;
        }
    }    
    if (!s.empty())
        throw(InvalidStructureException(" Pairs pending to close"));    
}
