/*
     _
    | |   ___  __ _ __ _ _  _
    | |__/ _ \/ _` / _` | || |
    |____\___/\__, \__, |\_, |
              |___/|___/ |__/
    A cross platform C++17 single-header
    console logging library.
    How do I use Loggey?
    there is an example application and docs are on the github:
    https://github.com/Spedzay/loggey/
    How do I change default colors?
    If your text editor supports searching, search for inside this file:
    LoggeySettings
    Contact me:
    - discord: on my github profile
    
    -- Begin MIT License. --
    Copyright (c) 2021 Spedzay
    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:
    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    -- End MIT License. --
    I do not reccomend using Loggey in its current state, its barley usable.
*/

// - loggey.h header guard
#ifndef LOGGEY_H
#define LOGGEY_H

#include <iostream>
#include <string>
#include <ctime>    
#include <iomanip>

// Check if we're on Windows or a Unix based system
#if defined(_WIN32) || defined(_WIN64)
#   define LOGGEY_WIN
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#   define LOGGEY_UNIX
#endif

// Operating System Specific #Defines and Includes
// Windows
#ifdef LOGGEY_WIN
// Windows specific includes and defines
#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#endif

// Unix
#ifdef LOGGEY_UNIX
#endif

namespace loggey {
    // All the colors loggey uses are in this namespace
    // Since the way console colors are handled differently on Unix and Windows we have seperate defines
    namespace colors {
#ifdef LOGGEY_WIN
        // Windows Color Codes
        constexpr uint8_t black = 0;
        constexpr uint8_t dark_blue = 1;
        constexpr uint8_t dark_green = 2;
        constexpr uint8_t light_blue = 3;
        constexpr uint8_t dark_red = 4;
        constexpr uint8_t magenta = 5;
        constexpr uint8_t orange = 6;
        constexpr uint8_t light_gray = 7;
        constexpr uint8_t gray = 8;
        constexpr uint8_t blue = 9;
        constexpr uint8_t green = 10;
        constexpr uint8_t cyan = 11;
        constexpr uint8_t red = 12;
        constexpr uint8_t pink = 13;
        constexpr uint8_t yellow = 14;
        constexpr uint8_t white = 15;
#endif // LOGGEY_WIN
#ifdef LOGGEY_UNIX
        // UNIX Color Codes
        constexpr uint8_t black = 30;
        constexpr uint8_t dark_blue = 34;
        constexpr uint8_t dark_green = 32;
        constexpr uint8_t light_blue = 36;
        constexpr uint8_t dark_red = 31;
        constexpr uint8_t magenta = 35;
        constexpr uint8_t orange = 33;
        constexpr uint8_t light_gray = 37;
        constexpr uint8_t gray = 90;
        constexpr uint8_t blue = 94;
        constexpr uint8_t green = 92;
        constexpr uint8_t cyan = 96;
        constexpr uint8_t red = 91;
        constexpr uint8_t pink = 95;
        constexpr uint8_t yellow = 93;
        constexpr uint8_t white = 97;
#endif // LOGGEY_UNIX
    }

    /*
         _
        | |   ___  __ _ __ _ _  _
        | |__/ _ \/ _` / _` | || |
        |____\___/\__, \__, |\_, |
         ___      |___/|___/ |__/
        / __| ___| |_| |_(_)_ _  __ _ ___
        \__ \/ -_)  _|  _| | ' \/ _` (_-<
        |___/\___|\__|\__|_|_||_\__, /__/
                                |___/
        LoggeySettings
        Change colors for Loggey Functions and Text!
        How do I use this??
        All the editable variables are in the loggey_settings namespace down below
    */
    namespace loggey_settings {
        // Flags
        static uint8_t flag_plus_color = loggey::colors::pink;
        static uint8_t flag_brackets_color = loggey::colors::light_gray;
        static uint8_t flag_time_color = loggey::colors::gray;

        // Generic
        static uint8_t text_color = loggey::colors::white;
        static uint8_t prefix_color = loggey::colors::red;
    }

    // Flags for logType's, What each flag does is documented on the github
    // When creating a logType with multiple flags do it like this:
    // addPlus | addPrefixEncasing | addTime
    // With a | to seperate each logType
    struct LogTypeFlags {
        enum Value {
            add_plus = 0x01,
            add_prefix_encasing = 0x02,
            add_time = 0x04
            //SOMETHING_ELSE = 0x10,
            //SOMETHING_COMPLETELY_DIFFERENT = 0x20
        };
    };

    // Set the console color. color codes are in loggey::loggey_settings
    inline void SetConsoleColor(uint8_t color)
    {
#ifdef LOGGEY_WIN
        static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, colors::black << 4 | color);
#endif // LOGGEY_WIN
#ifdef LOGGEY_UNIX
        const std::string color_output = "\033[" + std::to_string(color) + "m";
        std::cout << color_output;
#endif // LOGGEY_UNIX
    }


    // LogType is a type for defining different logs, heres an example: you want a LogType for erros and a LogType for warnings,
    // So we define a LogType called ERROR and set it to be red and its prefix as "ERROR" and with what flags we want!
    // Now when we call log() and pass in our ERROR LogType it will make a red log
    class LogType {
    public:
        uint8_t color = loggey_settings::prefix_color;  // Prefix Color
        std::string prefix; // Prefix text aka "PrefixExample: logText"
        int flags; // Flags aka addPlus will make it "[+] PrefixExample: logText"

        // ik this is bad but my ass cant figure out how to do it. (constructor overloading :vomit:)  i think this is the best way to do it, c++ 2021 fix when - stalin
        // TODO: ^
        LogType(uint8_t prefix_color, const std::string& prefix_text, int log_flag) {
            color = prefix_color;
            prefix = prefix_text;
            flags = log_flag;
        }
        LogType(uint8_t prefix_color, const std::string& prefix_text) {
            color = prefix_color;
            prefix = prefix_text;
        }
        LogType(const std::string& prefix_text) {
            prefix = prefix_text;
        }
        LogType(const std::string& prefix_text, int log_flag) {
            flags = log_flag;
            prefix = prefix_text;
        }
    };

    template <typename T>
    // log output to the console/terminal, this takes in a LogType and a string to log
    inline void log(const LogType& logtype, T log_text) {
        // If addTime is a flag from logtype we will add the time to the log
        if (logtype.flags & LogTypeFlags::add_time) {
            // Current date/time based on current system
            SetConsoleColor(loggey_settings::flag_time_color);

            auto time = std::time(nullptr);
            std::cout << std::put_time(std::localtime(&time), "%T") << " "; // ISO 8601 format.

        }

        // If addPlus is a flag from logtype we will add a [+] to the log.
        if (logtype.flags & LogTypeFlags::add_plus) {
            SetConsoleColor(loggey_settings::flag_brackets_color);  std::cout << "[";
            SetConsoleColor(loggey_settings::flag_plus_color); std::cout << "+";
            SetConsoleColor(loggey_settings::flag_brackets_color);  std::cout << "] ";
        }
        // If addPrefix is a flag from logtype we will add [this] around the prefix of the log.
        if (logtype.flags & LogTypeFlags::add_prefix_encasing) {
            SetConsoleColor(loggey_settings::flag_brackets_color); std::cout << "[";
            SetConsoleColor(logtype.color); std::cout << logtype.prefix;
            SetConsoleColor(loggey_settings::flag_brackets_color); std::cout << "] ";
        }

        // if theres no flags in logtype we will just write the colored prefix like normal.
        else {
            SetConsoleColor(logtype.color); std::cout << logtype.prefix << " ";
        }
        SetConsoleColor(loggey_settings::text_color); 
        std::cout << log_text << std::endl;;
    }

} // loggey
#endif // LOGGEY_H
