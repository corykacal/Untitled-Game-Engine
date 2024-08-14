//
// Created by Cory Kacal on 8/13/24.
//
#ifndef UNTITLED_MODELIDMANAGER_H
#define UNTITLED_MODELIDMANAGER_H

#include <mutex>
#include <queue>
#include <limits>
#include <stdexcept>

class ModelIdManager
{
    private:
        static std::mutex s_mutex;
        static std::queue<int> s_freeIds;
        static int s_nextId;

        ModelIdManager() = delete;
        ModelIdManager(const ModelIdManager&) = delete;
        ModelIdManager& operator=(const ModelIdManager&) = delete;

    public:
        static int getId() {
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

        static void freeId(int id) {
            if (id < 0) {
                throw std::invalid_argument("Invalid ID");
            }

            std::lock_guard<std::mutex> lock(s_mutex);
            s_freeIds.push(id);
        }
};

// Initialize static members
std::mutex ModelIdManager::s_mutex;
std::queue<int> ModelIdManager::s_freeIds;
int ModelIdManager::s_nextId = 0;

#endif //UNTITLED_MODELIDMANAGER_H
