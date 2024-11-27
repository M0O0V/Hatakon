#include "ISXOD.h"
#include "Validator.h"
#include "RecordMerger.h"
#include <fstream>
#include <sstream>

std::string FileProcessor::getIdFromLine(const std::string& line) 
{
    std::stringstream ss(line);
    std::string id;
    getline(ss, id, ',');
    return id;
}

// --------------------------------- Слияние данных строк с одинаковым ID
void FileProcessor::processData() 
 {
    if (lines.empty()) 
    {
        return;
    }

    for (const auto& line : lines) 
    {
        std::string id = getIdFromLine(line);
        groupedLines[id].push_back(line);
    }

    RecordMerger merger;
    
    for (auto& pair : groupedLines) 
    {
        if (pair.second.size() > 1) 
        {
            std::string mergedLine = pair.second[0];
            for (size_t i = 1; i < pair.second.size(); i++) 
            {
                mergedLine = merger.mergeRecords(mergedLine, pair.second[i]);
            }
            pair.second = {mergedLine};
        }
    }
}


// ---------------Слияние строк с одинаковым ID
void FileProcessor::mergeSimilarLines() 
{
    for (auto& [id, lineGroup] : groupedLines) 
    {
        if (lineGroup.size() > 1) 
        {
            std::string mergedLine = lineGroup[0];
            lineGroup = {mergedLine};
        }
    }
}

// ---------------Запсись в файл
void FileProcessor::writeResult(const std::string& filename) 
{
    std::ofstream outFile(filename);

    if (!outFile.is_open()) 
    {
        throw std::runtime_error("NO open file");
    }
    
    for (const auto& [id, lineGroup] : groupedLines) 
    {
        for (const auto& line : lineGroup) {
            outFile << line << "\n";
        }
    }
    outFile.close();
}

// --------------Чтение файла
void FileProcessor::readFile(const std::string& filename) 
{
    std::ifstream file(filename);
    std::string line;
    DataValidator validator;
    
    while (getline(file, line)) 
    {
        if (validator.isValidRecord(line)) 
            lines.push_back(line);
    }
}

