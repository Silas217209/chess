#pragma once

#include <string>

#define RESET "\e[38;5;m"
#define YELLOW "\e[38;5;226m"
#define RED "\e[38;5;196m"
#define GREEN "\e[38;5;46m"
#define BLUE "\e[38;5;33m"

constexpr auto red(std::string s) -> std::string { return RED + s + RESET; }

constexpr auto green(std::string s) -> std::string { return GREEN + s + RESET; }

constexpr auto blue(std::string s) -> std::string { return BLUE + s + RESET; }
