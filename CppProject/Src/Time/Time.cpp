#include "Time.h"

void Time::Init()
{
    _globalTimer.SetNow();
    _frameTimer.SetNow();
}

void Time::Update()
{
    auto deltaTimeInMacroSecond = _globalTimer.GetIntervalAndSetNow();
    _deltaTime = (double)deltaTimeInMacroSecond / 1000;
    _timeSinceBegin += _deltaTime;

    _frameTimer.SetNow();
}

double Time::DeltaTimeMilliSecond()
{
    return _deltaTime;
}

double Time::DeltaTimeSecond()
{
    return _deltaTime / 1000;
}

double Time::TimeSinceBegin()
{
    return _timeSinceBegin;
}

double Time::GetFrameTimerElapsed()
{
    auto deltaTimeInMacroSecond = _frameTimer.GetIntervalAndSetNow();
    return (double)deltaTimeInMacroSecond / 1000;
}


