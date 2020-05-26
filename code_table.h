#ifndef MEGAZIP_CODE_TABLE_H
#define MEGAZIP_CODE_TABLE_H

#include <unordered_map>
#include <string>

// TODO: replace with equivalent from Code class.
#define MAX_CODE 0xFFE // 2^12 - 2

class CodeTable {

    std::unordered_map<unsigned short, std::string> table;

public:

    CodeTable();

    [[nodiscard]] const std::string &getValue(const unsigned short &code) {
        return table.at(code);
    }

    [[nodiscard]] unsigned short getLastCode() {
        return table.size() - 1;
    }

    void updateValue(const unsigned short &code, const std::string &value);

    void putValue(const std::string &value);

    [[nodiscard]] bool contains(const unsigned short &code) const { return table.contains(code); };
};


#endif //MEGAZIP_CODE_TABLE_H
