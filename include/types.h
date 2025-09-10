#ifndef TYPES_H
#define TYPES_H

// ================================
// SIMULATION MODE ENUMS
// ================================

enum class SimulationMode {
    AUTOMATIC,        // Runs automatically with real-time dashboard
    STEP_BY_STEP,    // Step-by-step with manual advancement
    FAST_RUN         // Fast execution with final results only
};

// ================================
// CORE ENUMS
// ================================

enum class VehicleType {
    REGULAR = 0,
    FIRE_TRUCK = 1,
    AMBULANCE = 2
};

enum class NodeType {
    WAIT_NODE,
    TRAFFIC_CONTROLLER
};

enum class InputValidationResult {
    INPUT_VALID = 0,
    INVALID_ADJACENCY_MATRIX,
    UNREACHABLE_DESTINATION,
    INVALID_CAPACITY,
    INVALID_TRAFFIC_CONTROLLER,
    DISCONNECTED_GRAPH
};

#endif // TYPES_H