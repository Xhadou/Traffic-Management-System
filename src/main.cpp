#include "traffic_network.h"
#include "display.h"
#include <iostream>
#include <exception>

using namespace std;

int main(int argc, char* argv[]) {
    try {
        TrafficNetwork network;

        Display::print_header("TRAFFIC MANAGEMENT SYSTEM v3.0 - STEP-BY-STEP EDITION");

        cout << Display::BOLD << Display::CYAN;
        cout << "   _____            __  __ _         __  __                                   " << endl;
        cout << "  |_   _| __ __ _ / _|/ _(_) ___   |  \\/  | __ _ _ __   __ _  __ _  ___ _ __ " << endl;
        cout << "    | || '__/ _` | |_| |_| |/ __|  | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|" << endl;
        cout << "    | || | | (_| |  _|  _| | (__   | |  | | (_| | | | | (_| | (_| |  __/ |   " << endl;
        cout << "    |_||_|  \\__,_|_| |_| |_|\\___|  |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|   " << endl;
        cout << "                                                             |___/           " << endl;
        cout << Display::RESET << endl;

        cout << Display::BOLD << "Features:" << Display::RESET << endl;
        cout << Display::SUCCESS_ICON << " Step-by-step vehicle movement visualization" << endl;
        cout << Display::SUCCESS_ICON << " Real-time network state display" << endl;
        cout << Display::SUCCESS_ICON << " Interactive simulation control" << endl;
        cout << Display::SUCCESS_ICON << " Multiple simulation modes" << endl << endl;

        string input_file = "traffic_input.txt";
        if (argc > 1) {
            input_file = argv[1];
            cout << Display::INFO_ICON << " Using input file: " << input_file << endl;
        } else {
            cout << Display::INFO_ICON << " Using default input file: " << input_file << endl;
        }

        cout << endl;

        if (!network.initialize(input_file)) {
            cout << Display::WARNING_ICON << " Initialization failed, using default sample network..." << endl;
        } else {
            cout << Display::SUCCESS_ICON << " Network initialized successfully!" << endl;
        }

        cout << Display::INFO_ICON << " Starting simulation..." << endl;
        network.run_simulation();
        cout << Display::INFO_ICON << " Simulation completed." << endl;

        return 0;

    } catch (const exception& e) {
        cout << Display::ERROR_ICON << " Fatal error: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << Display::ERROR_ICON << " Unknown fatal error occurred" << endl;
        return 1;
    }
}