#include <random>
#include <limits>
#include "XXHashMap.h"
#include "xxhash/xxhash.h"

size_t XXHashString::_seed = GenerateSeed();

size_t XXHashString::operator()(const std::string& str)
{
    return XXH64(str.data(), str.size(), _seed);
}

size_t XXHashString::GenerateSeed()
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, std::numeric_limits<int>::max());
    return dist(generator);
}

size_t XXHashString::GetSeed()
{
    return _seed;
}
