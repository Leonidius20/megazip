#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <cstddef>
#include <memory>

class StringTable {
    std::unordered_map<std::string, std::unique_ptr<std::byte>> table;
public:
    StringTable();

    std::byte *getCode(const std::string &key) const { return table.at(key).get(); };

    bool contains(const std::string &key) const { return table.contains(key); }

    void addCode(const std::string &key);
};