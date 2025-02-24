#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <vector>

class FinalBlade {
public:
    explicit FinalBlade(const std::vector<int>&) {  // 避免vector<bool>特化问题
        throw std::runtime_error("FinalBlade initialization failed: Invalid parameter format (expected non-empty vector)");
    }
    FinalBlade(const FinalBlade&) = delete;
    FinalBlade& operator=(const FinalBlade&) = delete;
};

class SafeContainer {
public:
    SafeContainer() : ptr(std::make_unique<int[]>(100)) {}

    void generateData() {
        std::generate_n(ptr.get(), 100, [n=0]() mutable {  // 更安全的generate_n
            return n * n++;
        });
    }

private:
    std::unique_ptr<int[]> ptr;
};

int main() {
    std::vector<int> vec = {1, 2, 3};  // 更清晰的初始化语法
    
    vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());

    std::ofstream file("data.txt");
    if (!file) {
        std::cerr << "File open failed" << std::endl;
        return EXIT_FAILURE;
    }
    file << "Data written";
    file.close();  // 显式关闭文件
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
                throw;  // 重新抛出异常保证异常传播
            }
        });
        worker.join();
    } catch (const std::exception& e) {  // 捕获更通用的异常
        std::cerr << "Thread error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
