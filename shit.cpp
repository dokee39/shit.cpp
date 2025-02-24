#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <vector>
#include <future>

class FinalBlade {
public:
    explicit FinalBlade(const std::vector<int>& vec) {
        if (vec.empty()) {
            throw std::runtime_error("Invalid input vector (empty)");
        }
    }
    FinalBlade(const FinalBlade&) = delete;
    FinalBlade& operator=(const FinalBlade&) = delete;
};

class SafeContainer {
public:
    SafeContainer() : ptr(std::make_unique<int[]>(100)) {}

    void generateData() {
        std::generate_n(ptr.get(), 100, [n=0]() mutable {
            return n++ * n;
        });
    }

private:
    std::unique_ptr<int[]> ptr;
};

int main() {
    std::vector<int> vec = {1, 2, 3};
    
    vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());

    std::ofstream file("data.txt");
    if (!file) {
        std::cerr << "File open failed" << std::endl;
        return EXIT_FAILURE;
    }
    file << "Data written";
    if (!file.flush()) {
        std::cerr << "File write failed" << std::endl;
        return EXIT_FAILURE;
    }
    file.close();

    try {
        auto future = std::async(std::launch::async, [] {
            return std::make_unique<int>(42);
        });
        auto data = future.get();
    } catch (const std::exception& e) {
        std::cerr << "Async error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
