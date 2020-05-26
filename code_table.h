#pragma once

#include <unordered_map>
#include <string>
#include "code.h"

class CodeTable {

    std::unordered_map<Code, std::string> table;

public:

    CodeTable();

    [[nodiscard]] const std::string &getValue(const Code &code) {
        return table.at(code);
    }

    [[nodiscard]] Code getLastCode() {
        return Code(table.size() - 1);
    }

    void updateValue(const Code &code, const std::string &value);

    void putValue(const std::string &value);

    [[nodiscard]] bool contains(const Code &code) const { return table.contains(code); };
};
