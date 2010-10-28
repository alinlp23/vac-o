#include <string>
#include <mili/mili.h>

#include "RNAFold.h"

const FilePath RNAFold::IN = "fold.in";
const FilePath RNAFold::OUT = "fold.out";
const Command RNAFold::CMD = "RNAfold -noPS < "+ RNAFold::IN + " > " + RNAFold::OUT;
const FileLineNo RNAFold::LINE_NO = 1;

Fe RNAFold::fold(const NucSequence& sequence, SecStructure& structure) const throw(RNABackendException)
{            
    FileLine sseq;
    for (size_t i=0; i<sequence.length(); ++i)
    {
        sseq += to_str(sequence[i])[0];
    }    
    write(IN, sseq);
    exec(CMD);
    
    /* fold.out look like this:
     * CGCAGGGAUCGCAGGUACCCCGCAGGCGCAGAUACCCUA
     * ...(((((((....(..((.....))..).))).)))). (-10.80)
    */
    FileLine aux;
    read_line(OUT, LINE_NO, aux);

    read_value(aux, 0, sequence.length(), structure);

    Fe energy;
    read_free_energy(aux, sequence.length(), energy);
    return energy;
}

size_t RNAFold::read_free_energy(FileLine& line, size_t offset, Fe& energy) const throw(RNABackendException)
{    
    try
    {
        const size_t from = ensure_found(line.find_first_of("(", offset)) + 1;
        const size_t to = ensure_found(line.find_first_of(")", from)) - 1;
        read_value(line, from, to-from, energy);
        return to;
    }
    catch (const StringNotFound& e)
    {
        throw RNABackendException("Could not read free energy");
    }    
}