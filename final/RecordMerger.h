#ifndef RECORD_MERGER_H
#define RECORD_MERGER_H

#include <string>
#include <vector>

class RecordMerger {
private:
    std::vector<std::string> splitRecord(const std::string& record);
    std::string joinFields(const std::vector<std::string>& fields);
    bool isEmptyField(const std::string& field);

public:
    std::string mergeRecords(const std::string& record1, const std::string& record2);
};

#endif