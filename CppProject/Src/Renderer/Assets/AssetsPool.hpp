#pragma once

#include <string>

#include "Define/Define.h"
#include "Util/NonConstructible.h"
#include "Util/XXHash/XXHashMap.h"

namespace Renderer
{
    template<class T>
    class AssetsPool: public NonConstructible
    {
    public:
        static Ptr<T> Get(const std::string& path)
        {
            auto findResult = _pool.find(path);
            if (findResult != _pool.end())
                return findResult->second;

            Ptr<T> pResult = std::make_shared<T>();
            pResult->Load(path);

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