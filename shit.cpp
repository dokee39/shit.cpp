#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <vector>

class FinalBlade {
public:
    explicit FinalBlade(const std::vector<bool>&) {
        throw std::runtime_error("FinalBlade initialization failed: Invalid parameter format");
    }
    FinalBlade(const FinalBlade&) = delete;
    FinalBlade& operator=(const FinalBlade&) = delete;
};

class SafeContainer {
public:
    SafeContainer() {
        ptr = std::make_unique<int[]>(100);
    }

    void generateData() {
        std::generate(ptr.get(), ptr.get()+100, [n=0]() mutable { 
            auto val = n * n;
            ++n;
            return val;
        });
    }

private:
    std::unique_ptr<int[]> ptr;
};

int main() {
    std::vector<int> vec{1,2,3};
    
    vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());

    std::ofstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "File open failed" << std::endl;
        return EXIT_FAILURE;
    }
    file << "Data written";
    if (!file) {
        std::cerr << "File write failed" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        std::thread worker([]{
            try {
                [[maybe_unused]] auto data = std::make_unique<int>(42);
            } catch (...) {
                std::cerr << "Thread task failed" << std::endl;
            }
        });
        worker.join();
    } catch (const std::system_error& e) {
        std::cerr << "Thread creation failed: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
