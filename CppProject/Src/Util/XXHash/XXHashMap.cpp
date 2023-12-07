
#include "XXHashMap.h"
#include "xxhash/xxhash.h"

static size_t gXXHashSeed = 19679263527;

size_t StringXXHashGenerator::operator()(const std::string& str) const
{
    return XXH64(str.data(), str.size(), gXXHashSeed);
}
