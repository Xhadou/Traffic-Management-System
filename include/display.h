#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>

using namespace std;

// ================================
// TERMINAL DISPLAY UTILITIES
// ================================

namespace Display {
    // ASCII-safe box drawing characters
    extern const string TOP_LEFT;
    extern const string TOP_RIGHT;
    extern const string BOTTOM_LEFT;
    extern const string BOTTOM_RIGHT;
    extern const string HORIZONTAL;
    extern const string VERTICAL;
    extern const string CROSS;
    extern const string TEE_DOWN;
    extern const string TEE_UP;
    extern const string TEE_RIGHT;
    extern const string TEE_LEFT;

    // Progress bar characters
    extern const string FULL_BLOCK;
    extern const string EMPTY_BLOCK;
    extern const string PARTIAL_BLOCK;

    // Status indicators
    extern const string SUCCESS_ICON;
    extern const string WARNING_ICON;
    extern const string ERROR_ICON;
    extern const string INFO_ICON;
    extern const string EMERGENCY_ICON;
    extern const string MOVE_ICON;
    extern const string STEP_ICON;

    // ANSI color codes (safe fallback)
    extern const string RESET;
    extern const string BOLD;
    extern const string RED;
    extern const string GREEN;
    extern const string YELLOW;
    extern const string BLUE;
    extern const string MAGENTA;
    extern const string CYAN;
    extern const string WHITE;

    // Function declarations
    void clear_screen();
    void print_header(const string& title);
    void print_section_header(const string& section);
    void print_progress_bar(double percentage, int width = 50);
    void print_separator();
    string get_vehicle_color(const string& type);
    string get_status_color(const string& status);
    void wait_for_enter();
    void print_step_separator();
}

#endif // DISPLAY_H