#include "Time.h"

void Time::Init()
{
    _timer.SetNow();
}

void Time::Update()
{
    auto deltaTimeInMacroSecond = _timer.GetIntervalAndSetNow();
    _deltaTime = (double)deltaTimeInMacroSecond / 1000;
    _timeSinceBegin += _deltaTime;
}

double Time::DeltaTime()
{
    return _deltaTime;
}

double Time::TimeSinceBegin()
{
    return _timeSinceBegin;
}


