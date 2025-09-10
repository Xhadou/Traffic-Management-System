#ifndef TRAFFIC_NETWORK_H
#define TRAFFIC_NETWORK_H

#include "types.h"
#include "data_structures.h"
#include "thread_pool.h"
#include "traffic_validator.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <string>
#include <fstream>

using namespace std;

// ================================
// MAIN TRAFFIC NETWORK CLASS
// ================================

class TrafficNetwork {
private:
    vector<NodeData> nodes;
    vector<vector<int>> adjacency_matrix;
    unordered_map<int, int> destinations;

    mutable mutex global_coordinator_mutex;
    mutable mutex stats_mutex;
    mutable mutex step_mutex;
    condition_variable cv_token_allocation;
    condition_variable cv_step_advance;

    SystemConfig config;
    SystemStats stats;
    unique_ptr<ThreadPool> thread_pool;
    TrafficValidator validator;

    atomic<bool> simulation_running{false};
    atomic<bool> shutdown_requested{false};
    atomic<bool> step_ready{false};
    atomic<bool> waiting_for_step{false};
    atomic<int> next_vehicle_id{1};
    atomic<int> active_threads{0};

public:
    TrafficNetwork();
    ~TrafficNetwork();

    bool initialize(const string& input_file);
    void run_simulation();

private:
    // Simulation mode selection
    void select_simulation_mode();

    // Step-by-step simulation methods
    void run_step_by_step_simulation();
    bool execute_single_step();
    bool process_single_vehicle_movement(size_t node_idx);
    bool process_vehicle_step_by_step(Vehicle& vehicle, size_t from_node, bool is_emergency);
    void perform_vehicle_move_with_display(Vehicle& vehicle, size_t from_node, int to_node);

    // Automatic simulation methods
    void run_automatic_simulation();

    // Display methods
    void display_initial_state();
    void display_current_state();
    void display_node_status_table();
    void display_quick_stats();
    void display_network_summary();
    void display_simulation_start();
    void display_shutdown_message();
    void display_enhanced_real_time_stats();
    void display_enhanced_node_table();
    void display_performance_dashboard();
    void display_activity_summary();
    void display_final_report();

    // Input/output methods
    bool load_input(const string& filename);
    void parse_config_sections(ifstream& file, int n);
    void parse_section_line(const string& line, const string& section,
                          unordered_map<char, int>& capacities,
                          unordered_set<char>& controllers,
                          unordered_map<char, int>& traffic,
                          unordered_map<char, int>& ambulances,
                          unordered_map<char, int>& fire_trucks, int n);
    void apply_configuration(const unordered_map<char, int>& capacities,
                           const unordered_set<char>& controllers,
                           const unordered_map<char, int>& traffic,
                           const unordered_map<char, int>& ambulances,
                           const unordered_map<char, int>& fire_trucks, int n);
    void add_vehicles_to_nodes(const unordered_map<char, int>& traffic,
                             const unordered_map<char, int>& ambulances,
                             const unordered_map<char, int>& fire_trucks, int n);
    bool create_sample_input();
    void add_sample_vehicles();

    // Threading methods
    void token_allocation_loop();
    void process_node_vehicles(size_t node_idx);
    void process_vehicle(Vehicle& vehicle, size_t from_node, bool is_emergency);
    void traffic_processing_loop(size_t node_idx);
    void ui_update_loop();

    // Vehicle movement methods
    void return_vehicle_to_queue(Vehicle& vehicle, size_t node_idx, bool is_emergency);
    int find_best_next_hop(size_t from_node, int destination);
    bool can_move_to_node_safe(int node_idx, VehicleType vehicle_type);
    void perform_vehicle_move(Vehicle& vehicle, size_t from_node, int to_node);
    void attempt_rerouting(Vehicle& vehicle, size_t current_node);

    // Utility methods
    void shutdown();
};

#endif // TRAFFIC_NETWORK_H