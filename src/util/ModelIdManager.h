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
        static int getId();
        static void freeId(int id);
};

#endif //UNTITLED_MODELIDMANAGER_H