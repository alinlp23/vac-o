#include "RNABackendProxy.h"

void write(const FilePath& file, FileLinesCt& lines) throw(RNABackendException)
{
    std::ofstream out;
    out.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    try{
        out.open(file.c_str());
        CAutonomousIterator<FileLinesCt> it(lines);
        while (!it.end())
        {
            out << *it << std::endl;
            ++it;
        }
    }
    catch (const std::ifstream::failure& e)
    {
        throw RNABackendException("An error ocurred trying to write "+file);
    }    
}

void write(const FilePath& file, FileLine& line) throw(RNABackendException)
{
    std::ofstream out;
    out.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        out.open(file.c_str());
        out << line << std::endl;
    }
    catch (const std::ifstream::failure& e)
    {
        throw RNABackendException("An error ocurred trying to write "+file);
    }    
}

void read_line(const FilePath& file, FileLineNo lineno, FileLine& line) throw(RNABackendException)
{
    std::ifstream in;
    in.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        in.open(file.c_str());
        if (lineno > 0)
        {
            string aux;
            for (size_t i=0; i<lineno; ++i)
            {
                getline(in, aux);
            }
        }
        getline(in, line);
    }
    catch (const std::ifstream::failure& e)
    {
        throw RNABackendException("An error ocurred trying to read "+file);
    }    
}
