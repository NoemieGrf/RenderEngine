#pragma once

#include <string>
#include <unordered_map>

template<typename T>
class XXHashGenerator
{
public:
    size_t operator()(const T& input) const
    {
        return XXH64(input.data(), input.size(), _seed);
    }

private:
    inline static size_t _seed = 19679263527;
};

template<typename T, typename F>
using XXHashMap = std::unordered_map<T, F, XXHashGenerator<T>>;