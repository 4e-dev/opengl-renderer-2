#ifndef LOG_H
#define LOG_H

#include <print>
#include <string>

enum LOG_TYPE {
    SUCCESS,
    ERROR,
    FAIL,
    WARN,
};

inline void log(
        std::string_view message,
        const LOG_TYPE log_type,
        const char* file = nullptr,
        const int line = -1) {
    /*
       Colors text based on its significance (likely a failure/error)
       and prints it to stdout.

       More on ANSI Escape Sequences
       https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
       */

    constexpr auto RESET    = "\x1B[0m"; // resets color, style, and weight
    constexpr auto RED      = "\x1B[31m";
    constexpr auto GREEN    = "\x1B[32m";
    constexpr auto YELLOW   = "\x1B[33m";

    std::string color {};

    switch (log_type) {
        case SUCCESS:
            color = GREEN;
            break;
        case ERROR:
        case FAIL:
            color = RED;
            break;
        case WARN:
            color = YELLOW;
            break;
    }

    bool no_debug_line = file == nullptr && line == -1;
    if (no_debug_line) {
        std::println("{}{}{}", color, message, RESET);
    } else {
        std::println("{}{}{} ({}:{})", color, message, RESET, file, line);
    }
}

#endif // LOG_H
