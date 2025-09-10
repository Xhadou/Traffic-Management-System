#include "data_structures.h"
#include <string>

using namespace std;
using namespace chrono;

// ================================
// VEHICLE IMPLEMENTATION
// ================================

Vehicle::Vehicle(int id, VehicleType t, int src, int dest)
    : vehicle_id(id), type(t), source_node(src), destination_node(dest),
      current_node(src), arrival_time(steady_clock::now()),
      start_time(steady_clock::now()) {}

bool Vehicle::operator<(const Vehicle& other) const {
    if (type != other.type) {
        return static_cast<int>(type) < static_cast<int>(other.type);
    }
    return arrival_time > other.arrival_time;
}

double Vehicle::get_priority_weight() const {
    switch(type) {
        case VehicleType::AMBULANCE: return 10.0;
        case VehicleType::FIRE_TRUCK: return 8.0;
        default: return 1.0;
    }
}

string Vehicle::to_string() const {
    string type_str = (type == VehicleType::AMBULANCE) ? "AMB" :
                     (type == VehicleType::FIRE_TRUCK) ? "FIRE" : "REG";
    return "[" + type_str + "-" + std::to_string(vehicle_id) + "]";
}

string Vehicle::get_type_display() const {
    switch(type) {
        case VehicleType::AMBULANCE: return "Ambulance";
        case VehicleType::FIRE_TRUCK: return "Fire Truck";
        default: return "Regular";
    }
}

// ================================
// NODE DATA IMPLEMENTATION
// ================================

NodeData::NodeData(int id, char c, NodeType t, int cap)
    : node_id(id), node_char(c), type(t), capacity(cap),
      last_token_time(steady_clock::now()) {}

bool NodeData::is_at_capacity() const { 
    return current_vehicles >= capacity; 
}

bool NodeData::has_emergency_vehicles() const { 
    return !emergency_queue.empty(); 
}

int NodeData::get_queue_size() const { 
    return waiting_queue.size() + emergency_queue.size(); 
}

double NodeData::get_utilization() const {
    return capacity > 0 ? (double)current_vehicles / capacity * 100.0 : 0.0;
}

string NodeData::get_status() const {
    double util = get_utilization();
    if (util >= 90.0) return "CRITICAL";
    if (util >= 75.0) return "HIGH";
    if (util >= 50.0) return "NORMAL";
    return "LOW";
}

string NodeData::get_type_display() const {
    return (type == NodeType::TRAFFIC_CONTROLLER) ? "Traffic Controller" : "Wait Node";
}

// ================================
// SYSTEM CONFIG IMPLEMENTATION
// ================================

void SystemConfig::load_defaults() {
    // Default values are already set in the header
}

// ================================
// SYSTEM STATS IMPLEMENTATION
// ================================

SystemStats::SystemStats() : start_time(steady_clock::now()) {}

double SystemStats::get_success_rate() const {
    int total = total_vehicles_processed + emergency_vehicles_processed;
    return total > 0 ? (double)successful_routes / total * 100.0 : 0.0;
}

double SystemStats::get_throughput() const {
    auto elapsed = duration_cast<seconds>(steady_clock::now() - start_time).count();
    return elapsed > 0 ? (double)total_moves / elapsed : 0.0;
}