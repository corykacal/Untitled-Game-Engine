#include "ModelIdManager.h"

// Define static members
std::mutex ModelIdManager::s_mutex;
std::queue<int> ModelIdManager::s_freeIds;
int ModelIdManager::s_nextId = 0;

// Implement methods
int ModelIdManager::getId() {
    std::lock_guard<std::mutex> lock(s_mutex);

    if (!s_freeIds.empty()) {
        int id = s_freeIds.front();
        s_freeIds.pop();
        return id;
    }

    if (s_nextId == std::numeric_limits<int>::max()) {
        throw std::runtime_error("No more IDs available");
    }

    return s_nextId++;
}

void ModelIdManager::freeId(int id) {
    if (id < 0) {
        throw std::invalid_argument("Invalid ID");
    }

    std::lock_guard<std::mutex> lock(s_mutex);
    s_freeIds.push(id);
}