#ifndef PERFORMANCE_TEST_H
#define PERFORMANCE_TEST_H

#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>
#include <iomanip>

class PerformanceTest {
private:
    static std::chrono::high_resolution_clock::time_point startTime;
    static std::vector<long long> durations;
    static size_t maxSamples;
    static long long highestDuration;
    static long long lowestDuration;
    static bool useFPS;

public:
    static void Start() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    static void End() {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        long long currentDuration = duration.count();

        durations.push_back(currentDuration);
        if (durations.size() > maxSamples) {
            durations.erase(durations.begin());
        }

        highestDuration = std::max(highestDuration, currentDuration);
        lowestDuration = std::min(lowestDuration, currentDuration);

        long long sum = std::accumulate(durations.begin(), durations.end(), 0LL);
        double average = static_cast<double>(sum) / durations.size();

        if (useFPS) {
            double currentFPS = 1000000.0 / currentDuration;
            double averageFPS = 1000000.0 / average;
            double highestFPS = 1000000.0 / lowestDuration;
            double lowestFPS = 1000000.0 / highestDuration;

            std::cout << std::fixed << std::setprecision(2)
                      << "Performance (FPS):\n"
                      << "  Current: " << currentFPS << "\n"
                      << "  Average: " << averageFPS << "\n"
                      << "  Highest: " << highestFPS << "\n"
                      << "  Lowest:  " << lowestFPS << std::endl;
        } else {
            std::cout << std::fixed << std::setprecision(2)
                      << "Execution times (µs):\n"
                      << "  Current: " << currentDuration << "\n"
                      << "  Average: " << average << "\n"
                      << "  Highest: " << highestDuration << "\n"
                      << "  Lowest:  " << lowestDuration << std::endl;
        }
    }

    static void SetMaxSamples(size_t samples) {
        maxSamples = samples;
    }

    static void Reset() {
        durations.clear();
        highestDuration = std::numeric_limits<long long>::min();
        lowestDuration = std::numeric_limits<long long>::max();
        std::cout << "Performance statistics have been reset." << std::endl;
    }

    static void UseFPS(bool use) {
        useFPS = use;
    }
};

std::chrono::high_resolution_clock::time_point PerformanceTest::startTime;
std::vector<long long> PerformanceTest::durations;
size_t PerformanceTest::maxSamples = 100; // Default to 100 samples
long long PerformanceTest::highestDuration = std::numeric_limits<long long>::min();
long long PerformanceTest::lowestDuration = std::numeric_limits<long long>::max();
bool PerformanceTest::useFPS = false; // Default to using microseconds

#endif // PERFORMANCE_TEST_H