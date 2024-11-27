#include "recordmerger.h"
#include <sstream>

// ------------------------------- РАЗБОР СТРОКИ 1
std::vector<std::string> RecordMerger::splitRecord(const std::string& record) 
{
    std::vector<std::string> fields;
    std::stringstream ss(record);
    std::string field;
    
    while (getline(ss, field, ',')) 
    {
        fields.push_back(field);
    }

    return fields;
}

// Поле пустое или содержит только пробелы и тп
// НЕ РЕАЛИЗОВАНО
// ДОРАБОТАТЬ
bool RecordMerger::isEmptyField(const std::string& field)
{
    return field.empty() || field == "\"\"" || field == "Н" || field == " ";
}

// Объединяет поля в одну строку через запятую
// сначала это потом вниз
std::string RecordMerger::joinFields(const std::vector<std::string>& fields)
{
    std::string result;
    for (size_t i = 0; i < fields.size(); i++) 
    {
        result += fields[i];

        if (i < fields.size() - 1) result += ",";
    }
    return result;
}

// Объединяет две линии в одну, заполняя пустые поля из второй записи
std::string RecordMerger::mergeRecords(const std::string& record1, const std::string& record2) 
{
    std::vector<std::string> fields1 = splitRecord(record1);
    std::vector<std::string> fields2 = splitRecord(record2);
    
    std::vector<std::string> mergedFields;
    
    for (size_t i = 0; i < fields1.size(); i++) 
    {
        if (i < fields2.size()) 
        {
            if (isEmptyField(fields1[i]) && !isEmptyField(fields2[i])) 
            {
                mergedFields.push_back(fields2[i]);
            } 
            else 
            {
                mergedFields.push_back(fields1[i]);
            }
        }
        else 
        {
            mergedFields.push_back(fields1[i]);
        }
    }
    
    return joinFields(mergedFields);
}