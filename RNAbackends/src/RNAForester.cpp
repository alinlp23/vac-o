#include "RNAForester.h"

const FilePath RNAForester::IN = "forester.in";
const FilePath RNAForester::OUT = "forester.out";
const Command RNAForester::CMD = "RNAforester -r --score -f "+ RNAForester::IN +" > "+RNAForester::OUT;
const FileLineNo RNAForester::LINE_NO = 1;

Similitude RNAForester::compare(const SecStructure& struct1,
                                const SecStructure& struct2) const throw(RNABackendException)
{    
    FileLinesCt lines;
    insert_into(lines, struct1);
    insert_into(lines, struct2);

    write(IN, lines);
    exec(CMD);

    FileLine aux;
    read_line(OUT, LINE_NO, aux);

    Similitude s;
    read_value(aux, s);
    return s;
}
