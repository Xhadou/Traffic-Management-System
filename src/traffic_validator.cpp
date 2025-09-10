#include "traffic_validator.h"
#include <stack>
#include <queue>

using namespace std;

InputValidationResult TrafficValidator::validate_input(const vector<vector<int>>& adj_matrix,
                                                     const vector<NodeData>& nodes,
                                                     const unordered_map<int, int>& destinations) {
    if (!is_graph_connected(adj_matrix)) {
        return InputValidationResult::DISCONNECTED_GRAPH;
    }
    if (!are_destinations_reachable(adj_matrix, destinations)) {
        return InputValidationResult::UNREACHABLE_DESTINATION;
    }
    for (const auto& node : nodes) {
        if (node.capacity <= 0) {
            return InputValidationResult::INVALID_CAPACITY;
        }
    }
    return InputValidationResult::INPUT_VALID;
}

bool TrafficValidator::is_graph_connected(const vector<vector<int>>& adj_matrix) {
    int n = adj_matrix.size();
    if (n == 0) return false;

    vector<bool> visited(n, false);
    stack<int> st;
    st.push(0);
    visited[0] = true;
    int count = 1;

    while (!st.empty()) {
        int curr = st.top();
        st.pop();

        for (int i = 0; i < n; ++i) {
            if (adj_matrix[curr][i] > 0 && !visited[i]) {
                visited[i] = true;
                st.push(i);
                count++;
            }
        }
    }
    return count == n;
}

bool TrafficValidator::are_destinations_reachable(const vector<vector<int>>& adj_matrix,
                                                const unordered_map<int, int>& destinations) {
    for (const auto& pair : destinations) {
        if (!is_path_exists(adj_matrix, pair.first, pair.second)) {
            return false;
        }
    }
    return true;
}

bool TrafficValidator::is_path_exists(const vector<vector<int>>& adj_matrix, int src, int dest) {
    int n = adj_matrix.size();
    if (src < 0 || src >= n || dest < 0 || dest >= n) return false;
    if (src == dest) return true;

    vector<bool> visited(n, false);
    queue<int> q;
    q.push(src);
    visited[src] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int i = 0; i < n; ++i) {
            if (adj_matrix[curr][i] > 0 && !visited[i]) {
                if (i == dest) return true;
                visited[i] = true;
                q.push(i);
            }
        }
    }
    return false;
}