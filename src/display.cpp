#include "display.h"
#include <iomanip>
#include <cstdlib>

using namespace std;

namespace Display {
    // ASCII-safe box drawing characters
    const string TOP_LEFT = "+";
    const string TOP_RIGHT = "+";
    const string BOTTOM_LEFT = "+";
    const string BOTTOM_RIGHT = "+";
    const string HORIZONTAL = "-";
    const string VERTICAL = "|";
    const string CROSS = "+";
    const string TEE_DOWN = "+";
    const string TEE_UP = "+";
    const string TEE_RIGHT = "+";
    const string TEE_LEFT = "+";

    // Progress bar characters
    const string FULL_BLOCK = "#";
    const string EMPTY_BLOCK = ".";
    const string PARTIAL_BLOCK = "=";

    // Status indicators
    const string SUCCESS_ICON = "[OK]";
    const string WARNING_ICON = "[!!]";
    const string ERROR_ICON = "[XX]";
    const string INFO_ICON = "[>>]";
    const string EMERGENCY_ICON = "[EM]";
    const string MOVE_ICON = "[->]";
    const string STEP_ICON = "[##]";

    // ANSI color codes (safe fallback)
    const string RESET = "\033[0m";
    const string BOLD = "\033[1m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";

    void clear_screen() {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }

    void print_header(const string& title) {
        cout << BOLD << CYAN;
        cout << "+" << string(78, '-') << "+" << endl;
        int total_width = 78;
        int title_len = title.length();
        int padding = (total_width - 2 - title_len) / 2; // -2 for the | characters
        int right_padding = total_width - 2 - title_len - padding;
        cout << "|" << string(padding, ' ') << title << string(right_padding, ' ') << "|" << endl;
        cout << "+" << string(78, '-') << "+" << RESET << endl;
    }

    void print_section_header(const string& section) {
        cout << BOLD << YELLOW << ">>> " << section << RESET << endl;
        cout << string(section.length() + 4, '=') << endl;
    }

    void print_progress_bar(double percentage, int width) {
        cout << "[";
        int filled = static_cast<int>(percentage * width / 100.0);
        for (int i = 0; i < width; ++i) {
            if (i < filled) cout << FULL_BLOCK;
            else cout << EMPTY_BLOCK;
        }
        cout << "] " << fixed << setprecision(1) << percentage << "%";
    }

    void print_separator() {
        cout << string(80, '-') << endl;
    }

    string get_vehicle_color(const string& type) {
        if (type.find("AMB") != string::npos) return RED;
        if (type.find("FIRE") != string::npos) return YELLOW;
        return GREEN;
    }

    string get_status_color(const string& status) {
        if (status == "CRITICAL") return RED;
        if (status == "HIGH") return YELLOW;
        if (status == "NORMAL") return GREEN;
        return WHITE;
    }

    void wait_for_enter() {
        cout << CYAN << "Press Enter to continue..." << RESET;
        cin.get();
    }

    void print_step_separator() {
        cout << BLUE << string(60, '=') << RESET << endl;
    }
}