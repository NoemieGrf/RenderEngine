#pragma once

#include <string>
#include <Helper/NonConstructible.h>

#include "Define/Define.h"
#include "ThirdParty/XXHash/XXHashMap.h"

namespace Renderer
{
    template<class T>
    class AssetsPool: public Helper::NonConstructible
    {
    public:
        static Ptr<T> Get(const std::string& path)
        {
            auto findResult = _pool.find(path);
            if (findResult != _pool.end())
                return findResult->second;

            Ptr<T> pResult = T::Create(path);
            _pool[path] = pResult;
            return pResult;
        }

        static void Remove(const std::string& path)
        {
            auto findResult = _pool.find(path);
            if (findResult != _pool.end())
                _pool.erase(findResult);
        }

    private:
        inline static XXHashMap<std::string, Ptr<T>> _pool;
    };
}