#pragma once

#include "Util/Timer/Timer.h"
#include "Util/NonConstructible.h"

class Time: public NonConstructible
{
public:
    static void Init();
    static void Update();
    static double DeltaTimeMilliSecond();
    static double DeltaTimeSecond();
    static double TimeSinceBegin();
    static double GetFrameTimerElapsed();

private:
    static inline Util::Timer _globalTimer = Util::Timer();
    static inline Util::Timer _frameTimer = Util::Timer();
    static inline double _deltaTime = 0;
    static inline double _timeSinceBegin = 0;
};