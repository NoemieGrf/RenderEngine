#pragma once

#include <queue>
#include <bitset>

class Application;
class ApplicationWinImp;

namespace Input
{
    class Keyboard
    {
    public:
        friend class ::Application;
        friend class ::ApplicationWinImp;

    public:
        Keyboard() = delete;
        ~Keyboard() = delete;
        Keyboard(const Keyboard&) = delete;
        Keyboard& operator= (const Keyboard&) = delete;

    public:
        class Event
        {
        public:
            enum class Type { Invalid, Press, Release };

        private:
            Type _type;
            unsigned char _code;

        public:
            Event();
            Event(Type type, unsigned char code);
            bool IsPressed() const;
            bool IsReleased() const;
            bool IsValid() const;
        };

    public:
        static bool IsKeyPressed(unsigned char keycode);
        static Event ReadKey();
        static bool IsKeyEmpty();
        static void ClearKey();

        static wchar_t ReadCharW();
        static bool IsCharEmpty();
        static void ClearChar();

        static void Clear();

        static void EnableAutoRepeat();
        static void DisableAutoRepeat();
        static bool IsAutoRepeatEnabled();

    private:
        static void OnKeyPressed(unsigned char keycode);
        static void OnKeyReleased(unsigned char keycode);
        static void OnCharW(wchar_t c);
        static void ClearState();

    private:
        static constexpr unsigned int NUM_OF_KEYS = 256;
        static constexpr unsigned int QUEUE_SIZE = 16;

    private:
        inline static bool _autoRepeat = false;
        inline static std::bitset<NUM_OF_KEYS> _keyStateSet;
        inline static std::queue<Event> _keyBuffer;
        inline static std::queue<wchar_t> _charBuffer;
    };
}
