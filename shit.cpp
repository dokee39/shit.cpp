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
            throw std::runtime_error("FinalBlade initialization failed: Invalid parameter format (expected non-empty vector)");
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
            int result = n * n;
            ++n;
 return;
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
    file.close();
    if (!file) {
        std::cerr << "File write failed" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        std::promise<void> prom;
        auto fut = prom.get_future();
        std::thread worker([&prom] {
            try {
                [[maybe_unused]] auto data = std::make_unique<int>(42);
                prom.set_value();
            } catch (...) {
                prom.set_exception(std::current_exception());
            }
        });
        worker.join();
        fut.get();
    } catch (const std::exception& e) {
        std::cerr << "Thread error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
