#pragma once

namespace Input
{
    enum KeyCode : int
    {
        None,

#pragma region Keyboard

        Escape, F1, F2, F3, F4, F5, F6,F7, F8, F9, F10, F11, F12,
        GraveAccent, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0, Minus, Equal, Backspace,
        Tab, Q, W, E, R, T, Y, U, I, O, P, LeftBracket, RightBracket, Backslash,
        CapsLock, A, S, D, F, G, H, J, K, L, Semicolon, Apostrophe, Enter,
        LeftShift, Z, X, C, V, B, N, M, Comma, Period, Slash, RightShift,
        LeftCtrl, LeftWin, LeftAlt, Space, RightAlt, RightWin, Fn, RightCtrl,
        PrintScreen, ScrollLock, Pause,
        Insert, Home, PageUp,
        Delete, End, PageDown,
        UpArrow, DownArrow, LeftArrow, RightArrow,
        F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
        NumLock, KeypadDivide, KeypadMultiply, KeypadSubtract,
        Keypad1, Keypad2, Keypad3, Keypad4, Keypad5, Keypad6, Keypad7, Keypad8, Keypad9, Keypad0,
        KeypadDecimal, KeypadAdd, KeypadEnter,
        AppBack, AppForward,

#pragma endregion

#pragma region GamePad

#pragma endregion

        Count,

    };

}