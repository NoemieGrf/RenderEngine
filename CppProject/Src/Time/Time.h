#pragma once

#include "Util/Timer/Timer.h"
#include "Util/NonConstructible.h"

class Time: public NonConstructible
{
public:
    static void Init();
    static void Update();
    static double DeltaTime();
    static double TimeSinceBegin();

private:
    static inline Util::Timer _timer = Util::Timer();
    static inline double _deltaTime = 0;
    static inline double _timeSinceBegin = 0;
};