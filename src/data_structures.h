#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "types.h"
#include <vector>
#include <queue>
#include <chrono>
#include <string>
#include <atomic>

using namespace std;

// ================================
// CORE DATA STRUCTURES
// ================================

struct Vehicle {
    int vehicle_id;
    VehicleType type;
    int source_node;
    int destination_node;
    int current_node;
    chrono::steady_clock::time_point arrival_time;
    chrono::steady_clock::time_point start_time;
    vector<int> path;
    int blocked_attempts = 0;

    Vehicle(int id, VehicleType t, int src, int dest);
    bool operator<(const Vehicle& other) const;
    double get_priority_weight() const;
    string to_string() const;
    string get_type_display() const;
};

struct NodeData {
    int node_id;
    char node_char;
    NodeType type;
    int capacity;
    int current_vehicles = 0;
    queue<Vehicle> waiting_queue;
    priority_queue<Vehicle> emergency_queue;
    vector<int> adjacent_nodes;
    chrono::steady_clock::time_point last_token_time;

    NodeData(int id, char c, NodeType t, int cap);
    bool is_at_capacity() const;
    bool has_emergency_vehicles() const;
    int get_queue_size() const;
    double get_utilization() const;
    string get_status() const;
    string get_type_display() const;
};

struct SystemConfig {
    SimulationMode mode = SimulationMode::STEP_BY_STEP;
    double token_cycle_duration = 0.5;
    double max_emergency_wait = 2.0;
    int retry_delay_ms = 100;
    double simulation_time = 20.0;
    double w1 = 0.5, w2 = 0.5, wa = 10.0, wf = 8.0;
    double max_block_time = 30.0;
    bool enable_colors = true;
    int console_refresh_rate = 1000;
    bool show_step_details = true;
    bool auto_advance_steps = false;

    void load_defaults();
};

struct SystemStats {
    int total_vehicles_processed = 0;
    int emergency_vehicles_processed = 0;
    double total_wait_time = 0.0;
    double total_journey_time = 0.0;
    int successful_routes = 0;
    int rerouting_attempts = 0;
    int total_moves = 0;
    int step_count = 0;
    chrono::steady_clock::time_point start_time;

    SystemStats();
    double get_success_rate() const;
    double get_throughput() const;
};

#endif // DATA_STRUCTURES_H