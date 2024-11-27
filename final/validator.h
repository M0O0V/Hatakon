#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <vector>

class DataValidator {
private:
    bool hasValidId(const std::string& line);
    bool isAllCaps(const std::string& line);
    bool hasValidDate(const std::string& line);
    std::vector<std::string> splitLine(const std::string& line);

public:
    bool isValidRecord(const std::string& line);
};

#endif
