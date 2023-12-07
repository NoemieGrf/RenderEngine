#pragma once

#include <string>
#include <unordered_map>

class StringXXHashGenerator
{
public:
    size_t operator()(const std::string& str) const;
};

template<typename T>
using XxHashStringMap = std::unordered_map<std::string, T, StringXXHashGenerator>;