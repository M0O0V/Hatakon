#ifndef ISXOD_H
#define ISXOD_H

#include "sort.h"
#include <string>
#include <vector>
#include <map>

class FileProcessor 
{
private:

    Sort sorter;  
    std::vector<std::string> lines;
    std::map<std::string, std::vector<std::string>> groupedLines;
    
    std::string getIdFromLine(const std::string& line);
    void mergeSimilarLines(); 

public:

    void readFile(const std::string& filename);
    void processData();
    void writeResult(const std::string& filename);
};

#endif
