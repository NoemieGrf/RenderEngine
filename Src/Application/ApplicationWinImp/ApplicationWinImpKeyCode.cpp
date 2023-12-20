#include "ApplicationWinImp.h"
#include "Input/KeyCode.h"
#include "Util/Logger/Logger.h"

Input::KeyCode WinVirtualKeyToKeyCode(WPARAM wParam)
{
    switch (wParam)
    {
        case '0': return Input::KeyCode::Num0;
        case '1': return Input::KeyCode::Num1;
        case '2': return Input::KeyCode::Num2;
        case '3': return Input::KeyCode::Num3;
        case '4': return Input::KeyCode::Num4;
        case '5': return Input::KeyCode::Num5;
        case '6': return Input::KeyCode::Num6;
        case '7': return Input::KeyCode::Num7;
        case '8': return Input::KeyCode::Num8;
        case '9': return Input::KeyCode::Num9;

        case 'A': return Input::KeyCode::A;
        case 'B': return Input::KeyCode::B;
        case 'C': return Input::KeyCode::C;
        case 'D': return Input::KeyCode::D;
        case 'E': return Input::KeyCode::E;
        case 'F': return Input::KeyCode::F;
        case 'G': return Input::KeyCode::G;
        case 'H': return Input::KeyCode::H;
        case 'I': return Input::KeyCode::I;
        case 'J': return Input::KeyCode::J;
        case 'K': return Input::KeyCode::K;
        case 'L': return Input::KeyCode::L;
        case 'M': return Input::KeyCode::M;
        case 'N': return Input::KeyCode::N;
        case 'O': return Input::KeyCode::O;
        case 'P': return Input::KeyCode::P;
        case 'Q': return Input::KeyCode::Q;
        case 'R': return Input::KeyCode::R;
        case 'S': return Input::KeyCode::S;
        case 'T': return Input::KeyCode::T;
        case 'U': return Input::KeyCode::U;
        case 'V': return Input::KeyCode::V;
        case 'W': return Input::KeyCode::W;
        case 'X': return Input::KeyCode::X;
        case 'Y': return Input::KeyCode::Y;
        case 'Z': return Input::KeyCode::Z;

        case VK_F1: return Input::KeyCode::F1;
        case VK_F2: return Input::KeyCode::F2;
        case VK_F3: return Input::KeyCode::F3;
        case VK_F4: return Input::KeyCode::F4;
        case VK_F5: return Input::KeyCode::F5;
        case VK_F6: return Input::KeyCode::F6;
        case VK_F7: return Input::KeyCode::F7;
        case VK_F8: return Input::KeyCode::F8;
        case VK_F9: return Input::KeyCode::F9;
        case VK_F10: return Input::KeyCode::F10;
        case VK_F11: return Input::KeyCode::F11;
        case VK_F12: return Input::KeyCode::F12;
        case VK_F13: return Input::KeyCode::F13;
        case VK_F14: return Input::KeyCode::F14;
        case VK_F15: return Input::KeyCode::F15;
        case VK_F16: return Input::KeyCode::F16;
        case VK_F17: return Input::KeyCode::F17;
        case VK_F18: return Input::KeyCode::F18;
        case VK_F19: return Input::KeyCode::F19;
        case VK_F20: return Input::KeyCode::F20;
        case VK_F21: return Input::KeyCode::F21;
        case VK_F22: return Input::KeyCode::F22;
        case VK_F23: return Input::KeyCode::F23;
        case VK_F24: return Input::KeyCode::F24;

        case VK_OEM_1: return Input::KeyCode::Semicolon;
        case VK_OEM_2: return Input::KeyCode::Slash;
        case VK_OEM_3: return Input::KeyCode::GraveAccent;
        case VK_OEM_4: return Input::KeyCode::LeftBracket;
        case VK_OEM_5: return Input::KeyCode::Backslash;
        case VK_OEM_6: return Input::KeyCode::RightBracket;
        case VK_OEM_7: return Input::KeyCode::Apostrophe;

        case VK_OEM_PLUS: return Input::KeyCode::Equal;
        case VK_INSERT: return Input::KeyCode::Insert;
        case VK_DELETE: return Input::KeyCode::Delete;
        case VK_BACK: return Input::KeyCode::Backspace;
        case VK_SPACE: return Input::KeyCode::Space;
        case VK_TAB: return Input::KeyCode::Tab;
        case VK_RETURN: return Input::KeyCode::Enter;
        case VK_ESCAPE: return Input::KeyCode::Escape;
        case VK_OEM_COMMA: return Input::KeyCode::Comma;
        case VK_OEM_MINUS: return Input::KeyCode::Minus;
        case VK_OEM_PERIOD: return Input::KeyCode::Period;
        case VK_CAPITAL: return Input::KeyCode::CapsLock;
        case VK_SCROLL: return Input::KeyCode::ScrollLock;
        case VK_NUMLOCK: return Input::KeyCode::NumLock;
        case VK_SNAPSHOT: return Input::KeyCode::PrintScreen;
        case VK_PAUSE: return Input::KeyCode::Pause;
        case VK_LEFT: return Input::KeyCode::LeftArrow;
        case VK_RIGHT: return Input::KeyCode::RightArrow;
        case VK_UP: return Input::KeyCode::UpArrow;
        case VK_DOWN: return Input::KeyCode::DownArrow;
        case VK_PRIOR: return Input::KeyCode::PageUp;
        case VK_NEXT: return Input::KeyCode::PageDown;
        case VK_HOME: return Input::KeyCode::Home;
        case VK_END: return Input::KeyCode::End;

        case VK_NUMPAD0: return Input::KeyCode::Keypad0;
        case VK_NUMPAD1: return Input::KeyCode::Keypad1;
        case VK_NUMPAD2: return Input::KeyCode::Keypad2;
        case VK_NUMPAD3: return Input::KeyCode::Keypad3;
        case VK_NUMPAD4: return Input::KeyCode::Keypad4;
        case VK_NUMPAD5: return Input::KeyCode::Keypad5;
        case VK_NUMPAD6: return Input::KeyCode::Keypad6;
        case VK_NUMPAD7: return Input::KeyCode::Keypad7;
        case VK_NUMPAD8: return Input::KeyCode::Keypad8;
        case VK_NUMPAD9: return Input::KeyCode::Keypad9;

        case VK_DECIMAL: return Input::KeyCode::KeypadDecimal;
        case VK_DIVIDE: return Input::KeyCode::KeypadDivide;
        case VK_MULTIPLY: return Input::KeyCode::KeypadMultiply;
        case VK_SUBTRACT: return Input::KeyCode::KeypadSubtract;
        case VK_ADD: return Input::KeyCode::KeypadAdd;
        case VK_LSHIFT: return Input::KeyCode::LeftShift;
        case VK_LCONTROL: return Input::KeyCode::LeftCtrl;
        case VK_LMENU: return Input::KeyCode::LeftAlt;
        case VK_LWIN: return Input::KeyCode::LeftWin;
        case VK_RSHIFT: return Input::KeyCode::RightShift;
        case VK_RCONTROL: return Input::KeyCode::RightCtrl;
        case VK_RMENU: return Input::KeyCode::RightAlt;
        case VK_RWIN: return Input::KeyCode::RightWin;
        case VK_APPS: return Input::KeyCode::Fn;

        case VK_BROWSER_BACK: return Input::KeyCode::AppBack;
        case VK_BROWSER_FORWARD: return Input::KeyCode::AppForward;
    }

    Util::Logger::LogWarn("UnKnow input, WPara = 0x{:x}", wParam);

    return Input::KeyCode::None;
}
