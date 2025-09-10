#ifndef TRAFFIC_VALIDATOR_H
#define TRAFFIC_VALIDATOR_H

#include "types.h"
#include "data_structures.h"
#include <vector>
#include <unordered_map>

using namespace std;

// ================================
// TRAFFIC VALIDATOR
// ================================

class TrafficValidator {
public:
    InputValidationResult validate_input(const vector<vector<int>>& adj_matrix,
                                       const vector<NodeData>& nodes,
                                       const unordered_map<int, int>& destinations);

private:
    bool is_graph_connected(const vector<vector<int>>& adj_matrix);
    bool are_destinations_reachable(const vector<vector<int>>& adj_matrix,
                                  const unordered_map<int, int>& destinations);
    bool is_path_exists(const vector<vector<int>>& adj_matrix, int src, int dest);
};

#endif // TRAFFIC_VALIDATOR_H