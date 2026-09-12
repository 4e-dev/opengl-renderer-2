#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <print>
#include <string>

enum LOG_TYPE {
    ERROR,
    WARN,
};

void log(std::string_view message, const LOG_TYPE log_type);

int main() {
    // [GLFW / windowing]
    if (!glfwInit()) {
        log("FAILED::GLFW initialization.", ERROR);
        glfwTerminate();
        return 1;
    }

    glfwTerminate();
    return 0;
}

// TODO: refine this function; the switch statement should only change the final color (DRY)
void log(std::string_view message, const LOG_TYPE log_type) {
    // More on ANSI Escape Sequences
    // (https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)

    constexpr auto RESET    = "\x1B[0m"; // resets color, style, and weight
    constexpr auto RED      = "\x1B[31m";
    constexpr auto YELLOW   = "\x1B[33m";

    std::string final_color {};

    switch (log_type) {
        case ERROR:
            final_color = RED;
            break;
        case WARN:
            final_color = YELLOW;
            break;
    }

    std::println("{}{}{} ({} {})", final_color, message, RESET, __FILE__, __LINE__);
}
