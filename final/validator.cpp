#include "validator.h"
#include <sstream>
#include <algorithm>
#include <iostream>

// ------------------------------- РАЗБОР СТРОКИ 2
std::vector<std::string> DataValidator::splitLine(const std::string& line) 
{
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    
    while (getline(ss, field, ',')) 
    {
        fields.push_back(field);
    }
    return fields;
}

// ------------------------------- Проверка на ID
bool DataValidator::hasValidId(const std::string& line) 
{
    auto fields = splitLine(line);

    if (fields.empty() || fields[0].empty()) 
        return false;
    
    return std::all_of(fields[0].begin(), fields[0].end(), 
                      [](char c) { return std::isdigit(c); });
}

bool DataValidator::isAllCaps(const std::string& line)  // НЕ РАБОТАЕТ!!!
{
    auto fields = splitLine(line);
    if (fields.size() < 4) return true; 
    
    std::string surname = fields[3];
    std::string name = fields[1];
    std::string patronymic = fields[2];
    
    auto isWordAllCaps = [](const std::string& word) 
    {
        if(word.empty()) 
            return false;
        
        bool hasLetters = false;

        for(unsigned char c : word) 
        {
            if(std::isalpha(c)) 
            {
                hasLetters = true;
                if(std::islower(c)) 
                    return false;
            }
        }
        return hasLetters;
    };
    
    if(isWordAllCaps(name) || isWordAllCaps(surname) || isWordAllCaps(patronymic)) 
    {
        std::cout << "Removing caps line: " << line << std::endl;
        return true;
    }
    
    return false;
}

// ------------------------------- Проверка на дату рождения
bool DataValidator::hasValidDate(const std::string& line) 
{
    auto fields = splitLine(line);
    if (fields.size() < 6) return false;
    
    std::string date = fields[5];
    if (date.empty()) return false;
    
    std::stringstream ss(date);
    std::string year, month, day;

    getline(ss, year, '-');
    getline(ss, month, '-');
    getline(ss, day);
    
    return month != "00" && day != "00";
}

// ------------------------------- Проверка всех полей
bool DataValidator::isValidRecord(const std::string& line) 
{
    return hasValidId(line) && 
           !isAllCaps(line) && 
           hasValidDate(line);
}
