#pragma once

#include <string>
#include <unordered_map>

class XXHashString
{
public:
    size_t operator()(const std::string& str);

public:
    static size_t GetSeed();

private:
    static size_t _seed;
    static size_t GenerateSeed();
};


template<typename T>
using XxHashUMap = std::unordered_map<std::string, T, XXHashString>;